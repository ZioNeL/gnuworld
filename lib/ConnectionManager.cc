/**
 * ConnectionManager.cc
 * Author: Daniel Karrels (dan@karrels.com)
 * $Id: ConnectionManager.cc,v 1.1 2002/05/27 17:22:02 dan_karrels Exp $
 */

#include	<unistd.h>
#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/ioctl.h>
#include	<sys/time.h>
#include	<netinet/tcp.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>

#include	<new>
#include	<map>
#include	<string>
#include	<sstream>
#include	<iostream>

#include	<ctime>
#include	<cctype>
#include	<cstdlib>
#include	<cstring>
#include	<cstdio>
#include	<cassert>
#include	<cerrno>

#include	"ConnectionManager.h"
#include	"Connection.h"
#include	"ConnectionHandler.h"
#include	"Buffer.h"

using std::cout ;
using std::endl ;
using std::string ;
using std::list ;
using std::map ;
using std::nothrow ;
using std::stringstream ;
using gnuworld::Buffer ;

ConnectionManager::ConnectionManager( const time_t defaultTimeout,
	const char defaultDelimiter )
:	timeout( defaultTimeout ),
	delimiter( defaultDelimiter )
{}

ConnectionManager::~ConnectionManager()
{
// There is no reason to iterate through the eraseMap because
// that structure simply holds iterators to the connectionMap.
// Since the below loop invalidates all of those iterators, let's
// just be clean about it and clear the eraseMap now
eraseMap.clear() ;

// First iterate through the list of currently active/pending
// Connections
for( handlerMapType::iterator handlerItr = handlerMap.begin() ;
	handlerItr != handlerMap.end() ; ++handlerItr )
	{
	for( connectionMapType::iterator connectionItr = 
		handlerItr->second.begin() ;
		connectionItr != handlerItr->second.end() ;
		++connectionItr )
		{
		// Convenience variable
		// Obtain a pointer to the Connection object
		Connection* connectionPtr = connectionItr->second ;

		// Close this Connection's socket
		closeSocket( connectionPtr->getSockFD() ) ;

		// Deallocate the space for this Connection object
		delete connectionPtr ;
		}
	}

// Clean up, even if not strictly necessary, it's good habit
handlerMap.clear() ;
}

const Connection* ConnectionManager::Connect( ConnectionHandler* hPtr,
	const string& host,
	unsigned short int port,
	bool TCP )
{

// Handler must be valid
assert( hPtr != 0 ) ;

cout	<< "Connect> "
	<< host
	<< ":"
	<< port
	<< endl ;

// Allocate a new Connection object
Connection* newConnection = new (nothrow)
	Connection( host, port, TCP, delimiter ) ;
assert( newConnection != 0 ) ;

// Set the absolute time for this Connection's timeout to occur
newConnection->setStartTime( time( 0 ) + timeout ) ;

// The new connection will automatically set itself to the pending state

// Check if the hostname given is a hostname or numbers and dots
if( isIpAddress( host ) )
	{
	// Numbers and dots
	newConnection->setIP( host ) ;
	}
else
	{
	// Canonical host name
	newConnection->setIP( ipAddrOf( host ) ) ;

	// Make sure that lookup was successful
	// If it fails, ipAddrOf() returns an empty
	// string, and inet_addr() will crash
	if( newConnection->getIP().empty() )
		{
		// No good
		delete newConnection ;

		cout	<< "Connect> Unable to find valid IP"
			<< endl ;

		return 0 ;
		}
	} // else()

// Setup some basic options
struct sockaddr_in* addr = newConnection->getAddr() ;
addr->sin_family = AF_INET ;
addr->sin_port = htons( static_cast< u_short >( port ) ) ;
addr->sin_addr.s_addr = inet_addr( newConnection->getIP().c_str() ) ;

// Open a non-blocking socket
int sockFD = openSocket( TCP ) ;
if( -1 == sockFD )
	{
	delete newConnection ;

	cout	<< "Connect> openSocket() failed"
		<< endl ;

	return 0 ;
	}

// Update the new Connection object
newConnection->setSockFD( sockFD ) ;

// Attempt to initiate the connect.
// The socket is non-blocking, so a failure is expected
// In the case of a UDP socket, this call to ::connect() will just
// fill the socket address structure with relevant information
if( ::connect( sockFD, reinterpret_cast< sockaddr* >( addr ),
	sizeof( struct sockaddr_in ) ) < 0 )
	{
	// Let's check what the error was
	switch( errno )
		{
		case EISCONN:
			// EISCONN means the connection is successful
			// This will still work fine when another
			// connect() is attempted later
			break ;

		// EINPROGRESS means that the socket is nonblocking and
		// the connection attempt is in progress
		case EINPROGRESS:
			break ;

		// All other errors are failures
		default:
			// Close the socket
			closeSocket( newConnection->getSockFD() ) ;

			// Deallocate the Connection object and
			// set it to NULL for return to caller
			delete newConnection ;
			newConnection = 0 ;

			cout	<< "Connect> Error detected in connect()"
				<< ", errno: "
				<< strerror( errno )
				<< endl ;

			// No need to call OnConnectFail() here since
			// this method will return a NULL Connection
			// to the caller, which indicates that the
			// attempt failed.
			break ;
		} // switch()
	} // if()

if( newConnection != 0 )
	{
//	cout	<< "Connect> Adding new connection attempt: "
//		<< *newConnection
//		<< endl ;

	// Connection in progress
	// Add to the handlerMap
	bool status = handlerMap[ hPtr ].insert(
		connectionMapType::value_type(
		newConnection, newConnection ) ).second ;

	// It's possible the connection could fail (?)
	// Either way, the container is nice enough to tell us
	// if it was successful, so let's check.
	if( !status )
		{
		// Insertion failed
		// Close the socket
		closeSocket( newConnection->getSockFD() ) ;

		cout	<< "ConnectionManager::Connect> Failed to "
			<< "add new connection to handlerMap: "
			<< *newConnection
			<< endl ;

		// Deallocate and set to 0 for return to caller
		delete newConnection ;
		newConnection = 0 ;
		}
	}

// Return a pointer to the Connection object, whether or not
// it's NULL
return newConnection ;
}

bool ConnectionManager::DisconnectByHost( ConnectionHandler* hPtr,
	const string& hostname,
	unsigned short int port )
{
assert( hPtr != 0 ) ;

// Iterator variables
handlerMapType::iterator handlerItr = handlerMap.find( hPtr ) ;
if( handlerItr == handlerMap.end() )
	{
	// This ConnectionHandler has no Connections registered
	// *shrug*
	return false ;
	}

connectionMapType::iterator connectionItr = handlerItr->second.begin() ;

for( ; connectionItr != handlerItr->second.end() ; ++connectionItr )
	{
	// Store the address of the Connection object in connectionPtr
	Connection* connectionPtr = connectionItr->second ;

	// Compare port numbers
	if( (port == connectionPtr->getPort()) &&
		!strcasecmp( connectionPtr->getHostname().c_str(),
			hostname.c_str() ) )
		{
		// Found it
		break ;
		}
	} // for()

// Did we find it?
if( connectionItr == handlerItr->second.end() ) ;
	{
	// Nope
	return false ;
	}

cout	<< "ConnectionManager::DisconnectByHost> Sheduling connection "
	<< "for removal: "
	<< *(connectionItr->second)
	<< endl ;

// Schedule this connectionItr to be removed
scheduleErasure( hPtr, connectionItr ) ;

// We found the item to be removed, so return success
return true ;
}

bool ConnectionManager::DisconnectByIP( ConnectionHandler* hPtr,
	const string& IP,
	unsigned short int port )
{

assert( hPtr != 0 ) ;

// Iterator variables
handlerMapType::iterator handlerItr = handlerMap.find( hPtr ) ;
if( handlerItr == handlerMap.end() )
	{
	// This ConnectionHandler has no Connections registered
	// *shrug*
	return false ;
	}

connectionMapType::iterator connectionItr = handlerItr->second.begin() ;

for( ; connectionItr != handlerItr->second.end() ; ++connectionItr )
	{
	// Store the address of the Connection object in connectionPtr
	Connection* connectionPtr = connectionItr->second ;

	// Compare port numbers
	if( (port == connectionPtr->getPort()) &&
		(connectionPtr->getIP() == IP) )
		{
		// Found it
		break ;
		}
	} // for()

// Did we find it?
if( connectionItr == handlerItr->second.end() ) ;
	{
	// Nope
	return false ;
	}

cout	<< "ConnectionManager::DisconnectByIP> Sheduling connection "
	<< "for removal: "
	<< *(connectionItr->second)
	<< endl ;

// Add to eraseMap to be erased later in Poll()
scheduleErasure( hPtr, connectionItr ) ;

// We found the item to be removed, so return success
return true ;
}

bool ConnectionManager::Disconnect( ConnectionHandler* hPtr,
	Connection* cPtr )
{
// Public method, verify method arguments
assert( hPtr != 0 ) ;
assert( cPtr != 0 ) ;

// Attempt to locate the handler in the handler map
handlerMapType::iterator handlerItr = handlerMap.find( hPtr ) ;
if( handlerItr == handlerMap.end() )
	{
	// Handler not found
	return false ;
	}

// Attempt to locate the Connection in the handler's connectionMap
connectionMapType::iterator connectionItr =
	handlerItr->second.find( cPtr ) ;
if( connectionItr == handlerItr->second.end() )
	{
	// Connection was not found for this handler
	return false ;
	}

cout	<< "ConnectionManager::Disconnect> Sheduling connection "
	<< "for removal: "
	<< *cPtr
	<< endl ;

// Schedule the connection to be erased during the next call
// to Poll()
scheduleErasure( hPtr, connectionItr ) ;

return true ;
}

void ConnectionManager::Poll( long seconds, long milliseconds )
{

cout	<< "Poll()" << endl ;

// Only execute this method if:
// - The handlerMap is empty:no connections to check
// - The eraseMap is empty: no connections to close
if( handlerMap.empty() && eraseMap.empty() )
	{
	return ;
	}

// highestFD is passed to select() as the largest FD for which to
// obtain state information, if that bit is present in the below
// fd_set's
int highestFD = 0 ;

// These variables are used for select()
fd_set writefds ;
fd_set readfds ;
FD_ZERO( &writefds ) ;
FD_ZERO( &readfds ) ;

// Iterator through the table of Connection's to setup select()
// FD information
for( handlerMapType::iterator handlerItr = handlerMap.begin() ;
	handlerItr != handlerMap.end() ; ++handlerItr )
	{
	for( connectionMapType::iterator connectionItr =
		handlerItr->second.begin(),
		connectionEndItr = handlerItr->second.end() ;
		connectionItr != connectionEndItr ;
		++connectionItr )
		{

		// Create a couple of convenience variables
		Connection* connectionPtr = connectionItr->second ;
		int tempFD = connectionPtr->getSockFD() ;

		if( connectionPtr->isConnected() )
			{
			// This connection already connected
			// Check to see if we can read
			FD_SET( tempFD, &readfds ) ;

			// Is the connection's output buffer empty?
			if( !connectionPtr->outputBuffer.empty() )
				{
				// There is data present to be written
				FD_SET( tempFD, &writefds ) ;
				}
			}
		else if( connectionPtr->isListening() )
			{
			// Server socket, it is always pending :)
			FD_SET( tempFD, &readfds ) ;
			}
		else if( connectionPtr->isPending() )
			{
			// Not yet fully connected, check for write
			FD_SET( tempFD, &writefds ) ;
			}

		// Keep track of the highest FD
		if( tempFD > highestFD )
			{
			highestFD = tempFD ;
			}
		} // for( connectionItr )
	} // for( handlerItr )

//cout	<< "Poll> Attempting to read "
//	<< connectionMap.size()
//	<< " fd's"
//	<< endl ;

// fdCnt is the number of FD's returned by select()
// loopCnt is the max number of attempts for select()
int			fdCnt = -1,
			loopCnt = 10 ;

do
	{
	// timeval may be modified by select() on some systems,
	// so recreate it each time
	struct timeval to = { seconds, milliseconds } ;

	// Make sure to clear errno
	errno = 0 ;

	// Call select()
	// Block indefinitely if seconds is -1
	fdCnt = ::select( 1 + highestFD, &readfds, &writefds, 0,
		(-1 == seconds) ? NULL : &to ) ;
	} while( (EINTR == errno) && (--loopCnt >= 0) ) ;

if( fdCnt < 0 )
	{
	// Error in select()
	return ;
	}

if( 0 == fdCnt )
	{
	// No pending state changes
	return ;
	}

// This variable is used for checking timeouts
time_t now = ::time( 0 ) ;

for( handlerMapType::iterator handlerItr = handlerMap.begin() ;
	handlerItr != handlerMap.end() ; ++handlerItr )
	{
	// Convenience variable for the long loop ahead
	ConnectionHandler* hPtr = handlerItr->first ;

	// Use connectionItr.end() explicitly here because if the
	// map becomes empty during the course of this loop, the
	// iterator to the original connectionMap.end() will be invalid
	for( connectionMapType::iterator connectionItr =
		handlerItr->second.begin() ;
		connectionItr != handlerItr->second.end() ;
		++connectionItr )
		{

		// This variable indicates if the connection should be
		// kept (true) or removed (false) from the tables
		bool connectOK = true ;

		// Obtain a pointer to the Connection object being inspected
		Connection* connectionPtr = connectionItr->second ;

		// Temporary variable, this is the value of the current
		// Connection's socket (file) descriptor
		int tempFD = connectionPtr->getSockFD() ;

		if( connectionPtr->isConnected() )
			{
			// Check for ability to read
			if( FD_ISSET( tempFD, &readfds ) )
				{
				// Data available, or error
				// handleRead() will perform the read()/recv()
				// and distribute event to virtual methods
				// (including OnDisconnect())
				//
				// Connected sockets are always checked
				// for read
				connectOK = handleRead( hPtr,
					connectionPtr ) ;

				// Attempt to write any buffered data
				// if the connection is valid
				if( connectOK &&
					!connectionPtr->outputBuffer.empty() )
					{
					connectOK = handleWrite( hPtr,
						connectionPtr ) ;
					}
				} // if( FD_ISSET() )
			} // if( connectionPtr->isConnected() )

		// Next let's check if this is a listening (server) socket
		else if( connectionPtr->isListening() )
			{
			// Yup.  See if anyone is waiting to connect
			if( FD_ISSET( tempFD, &readfds ) )
				{
				// Could be, attempt an accept()
				connectOK = finishAccept( hPtr,
					connectionPtr ) ;
				}
			}

		// Check for pending outgoing connection
		else if( connectionPtr->isPending() )
			{
			// Ready for write state?
			if( FD_ISSET( tempFD, &writefds ) )
				{
				// Yup, attempt to complete the connection
				connectOK = finishConnect( hPtr,
					connectionPtr ) ;
				} // if( FD_ISSET() )
			else
				{
				// FD is NOT set, and the connection is
				// still pending; let's check for a timeout
				if( now >= (connectionPtr->getStartTime()
					+ timeout) )
					{
					// This connection attempt has
					// timed out
					// Notify the handler
					hPtr->OnTimeout( connectionPtr ) ;

					// Mark this connection for erasure
					connectOK = false ;

					} // if( now >= ... )
				} // else()
			} // if( connectionPtr->isPending() )

		// Check if the connection is still valid
		if( !connectOK )
			{
			// Nope, the connection is invalid
			// Schedule it for erasure
			scheduleErasure( hPtr, connectionItr ) ;
			} // if( !connectOK )

		} // for( connectionItr )
	} // for( handlerItr )

// Handler methods have the freedom to call Disconnect() at will,
// however disconnecting/deallocating Connection objects in a handler
// will invalidate the iterator used in the above loop (since handlers
// are called in the above loop).
// Therefore, we are using a separate container to hold pointers to
// the Connection objects to be erased, and are erasing them here
// in synchronous fashion to simplify the process.
// Elements can get themselves into the eraseMap by
// either having a read/write/accept/connect error, or by a client
// class calling some form of Disconnect().
// Either way, all terminal processing is done here.
//
// Note that the reason for using an associative container for the
// eraseMap, instead of a linear one, is to increase efficiency here.
// If the Connection*'s were unsorted in the eraseMap, then this
// loop would be performing many handlerMap.find()'s looking for the
// ConnectionHandler for each Connection.
// With the eraseMap being associative, we can work a single
// ConnectionHandler at a time to its completion, which saves
// lookups.
// No increment is done in this for loop, because it is done
// in the inner for loop.
// Because all Connections are erased by calling scheduleErasure(),
// we are guaranteed that an iterator to a connection is not entered
// into the eraseMap more than once.
//
for( eraseMapType::iterator eraseItr = eraseMap.begin(),
	eraseEndItr = eraseMap.end() ;
	eraseItr != eraseEndItr ; )
	{
	// First lookup the handlerItr.
	// No error checking is performed here, because the above
	// loop was able to find the handler, and no removes have
	// been done (it is done here).
	// Because the lookups are performed based on what is found
	// in the eraseMap, handlerItr is guaranteed to have
	// at least one Connection which must be removed.
	//
	handlerMapType::iterator handlerItr = handlerMap.find(
		eraseItr->first ) ;

	// Continue in the loop, erasing elements, until the
	// handler in the eraseMap changes
	// This loop guard will be evaluated to true at least once.
	// The below loop will terminate when either of two conditions
	// are present after incrementing eraseItr:
	// - eraseItr is equivalent to eraseEndItr
	// - eraseItr->first != handlerItr->first
	// Be sure to check both, beginning with the case that could
	// crash the process :)
	for( ; (eraseItr != eraseEndItr) &&
		(eraseItr->first == handlerItr->first) ; ++eraseItr )
		{
		Connection* connectionPtr = eraseItr->second->first ;

		cout	<< "Poll> Removing connection: "
			<< *connectionPtr
			<< endl ;

		// Close the Connection's socket (file) descriptor
		closeSocket( connectionPtr->getSockFD() ) ;

		// Deallocate the memory associated with the Connection
		delete connectionPtr ;

		// Remove the Connection from the connectionMap
		// for this handler
		handlerItr->second.erase( eraseItr->second ) ;

		} // for( ; eraseItr->first == handlerItr->first ; )

	} // for( eraseItr != eraseEndItr )
eraseMap.clear() ;

// Check if the connectionMap for any particular handler is empty
for( handlerMapType::iterator handlerItr = handlerMap.begin() ;
	handlerItr != handlerMap.end() ; )
	{
	// hash_map's invalidate iterators when an item is erase()'d
	// Therefore, if an item is erased in this loop, reset the
	// handlerItr to begin().  This should result in negligible
	// performance loss since the number of possible client *should*
	// be relatively small
	if( handlerItr->second.empty() )
		{
		// The connectionMap for this handler is empty
		// Erase it
		handlerMap.erase( handlerItr ) ;

		// Reset handlerItr
		handlerItr = handlerMap.begin() ;
		}
	else
		{
		// Items remain in this handler's connectionMap
		// Move to next handler
		++handlerItr ;
		}
	} // for()

//cout	<< "Poll> End"
//	<< endl ;

} // Poll()

int ConnectionManager::openSocket( bool TCP )
{

// Let's get right to it, open the socket
int sockFD = ::socket( AF_INET,
	(TCP) ? SOCK_STREAM : SOCK_DGRAM, 0 ) ;

if( !TCP )
	{
	cout	<< "openSocket> Opening UDP"
		<< endl ;
	}

// Was the socket creation successful?
if( sockFD < 0 )
	{
	// Nope
	cout	<< "openSocket> socket() failed: "
		<< strerror( errno )
		<< endl ;
	return -1 ;
	}

if( !setSocketOptions( sockFD ) )
	{
	close( sockFD ) ;

	cout	<< "openSocket> Failed to set SO_LINGER: "
		<< strerror( errno )
		<< endl ;

	return -1 ;
	}
return sockFD ;
}

// Static method, no const needed
bool ConnectionManager::isIpAddress( const string& host )
{
unsigned short int count = 0 ;

for( string::size_type i = 0 ; (i < host.size()) && (count < 4) ; ++i )
	{
	// characters in an IP address may only be
	// digits or decimal points
	if( '.' == host[ i ] )
		{
		count++ ;
		}
	else if( !isdigit( host[ i ] ) )
		{
		return false ;
		}
	}

// there are exactly three decimal points in an IP address
return (3 == count) ;
}

// Static, so no const necessary
string ConnectionManager::ipAddrOf( const string& host )
{
struct hostent *hostEntry = ::gethostbyname( host.c_str() ) ;
if( NULL == hostEntry )
	{
	return string() ;
	}

struct in_addr in ;
char **p = hostEntry->h_addr_list ;
memcpy( &in.s_addr, *p, sizeof( in.s_addr ) ) ;
char ipAddr[] = "000.000.000.000" ;
sprintf( ipAddr,"%s", inet_ntoa( in ) ) ;

return string( ipAddr ) ;
}

void ConnectionManager::closeSocket( int fd )
{
::close( fd ) ;
}

bool ConnectionManager::handleRead( ConnectionHandler* hPtr,
	Connection* c )
{
// protected member, no error checking

// Create and set a temporary buffer to 0
char buf[ 4096 ] ;
memset( buf, 0, 4096 ) ;

// Attempt the read from the socket
int readResult = ::recv( c->getSockFD(), buf, 4096, 0 ) ;

// Check for error on read()
if( readResult < 0 )
	{
	// Error on read, socket no longer valid
	hPtr->OnDisconnect( c ) ;

	// Read error
	return false ;
	}

// Read was successful

// Null terminate the buffer
// This shouldn't be necessary since the buffer was cleared
// above, but who knows what the system is doing :)
buf[ readResult ] = 0 ;

// Add to Connection input buffer
c->inputBuffer += buf ;

// Check if a complete command was read
string line ;
while( c->inputBuffer.ReadLine( line ) )
	{
	// Line available
	hPtr->OnRead( c, line ) ;
	}

return true ;
}

bool ConnectionManager::handleWrite( ConnectionHandler* hPtr,
	Connection* c )
{
// protected member, no error checking

// Attempt the write to the socket
// According to W. Richard Stevens, Unix Network Programming, Vol 1:
// If there is some room in the socket send buffer, the return value
// will be the number of bytes that the kernel was able to copy
// into the buffer. ( This is called a short count).
// Therefore, just place the entire Connection output buffer into
// the send(), and the system will send() as much as it can
int writeResult = ::send( c->getSockFD(),
	c->outputBuffer.c_str(),
	c->outputBuffer.size(),
	0 ) ;

// Check for write error
if( writeResult < 0 )
	{
	// Error on write, socket no longer valid
	hPtr->OnDisconnect( c ) ;

	// Write error
	return false ;
	}

// Successful write, update the Connection's output buffer
c->outputBuffer.Delete( writeResult ) ;

return true ;
}

bool ConnectionManager::finishConnect( ConnectionHandler* hPtr,
	Connection* c )
{
// Protected member method, no error checking performed on
// method arguments

//cout	<< "ConnectionManager::finishConnect> "
//	<< *c
//	<< endl ;

// Attempt to connect()
int connectResult = ::connect( c->getSockFD(),
	reinterpret_cast< sockaddr* >( c->getAddr() ),
	sizeof( struct sockaddr_in ) ) ;

// Was the connect successful?
if( connectResult < 0 )
	{
	// EISCONN means that the connection succeeded with the
	// first attempt
	if( errno != EISCONN )
		{
		cout	<< "finishConnect> Failed connect: "
			<< strerror( errno )
			<< endl ;

		// Unable to establish connection
		hPtr->OnConnectFail( c ) ;

		return false ;
		} // if( errno != EISCONN )
	}

// Update the Connection's state
c->setConnected() ;

// Notify listeners
hPtr->OnConnect( c ) ;

// Return success
return true ;
}

bool ConnectionManager::finishAccept( ConnectionHandler* hPtr,
	Connection* c )
{
// Protected member, no arguments verified here
// (c) is the server socket, which is listen()'ing

// Allocate and configure a new Connection object
Connection* newConnection = new (std::nothrow) Connection( delimiter ) ;
assert( newConnection != 0 ) ;

newConnection->setIncoming() ;
newConnection->setPending() ;
newConnection->setTCP( true ) ;
newConnection->setPort( c->getPort() ) ;

// len is the size of a sockaddr structure, for use by accept()
size_t len = sizeof( struct sockaddr ) ;

// Attempt to receive a pending connection.
// The socket descriptor passed in is that of te listening socket.
// The sockaddr structure is that of the new connection, and will be
// populated with host information of the connecting client.
// accept() returns the fd of the new connection, with "mostly"
// the same options as the server socket, or -1 on error.
int newFD = ::accept( c->getSockFD(),
	reinterpret_cast< sockaddr* >( newConnection->getAddr() ),
	static_cast< socklen_t* >( &len ) ) ;

/*
 * From man page:
 * There may not always be a connection waiting after a SIGIO
 * is delivered or select(2) or poll(2) return a  readability
 * event because the connection might have been removed by an
 * asynchronous network error or another thread before accept
 * is called.  If this happens then the call will block waiting for
 * the next connection to  arrive.   To  ensure  that
 * accept never blocks, the passed socket s needs to have the
 * O_NONBLOCK flag set.
 */
if( (newFD < 0) && (EAGAIN != errno) && (EWOULDBLOCK != errno))
	{
	// The only use of notifying the handler here is
	// so the handler can check for newConnection->isIncoming()
	// to know that an incoming connection failed; it can
	// obtain no other information about the Connection.
	hPtr->OnConnectFail( newConnection ) ;

	// Clean up memory
	delete newConnection ; newConnection = 0 ;

	// Return error
	return false ;
	}

newConnection->setConnected() ;
newConnection->setSockFD( newFD ) ;

const char* IP = inet_ntoa( newConnection->getAddr()->sin_addr ) ;
newConnection->setIP( IP ) ;

// From man page:
// Note that any per file descriptor flags (everything that can be  set
// with  the F_SETFL fcntl, like non blocking or async state)
// are not inherited across an accept().
if( !setSocketOptions( newFD ) )
	{
	// Failed to set socket options
	// The Connection now has the IP of the failed Connection
	hPtr->OnConnectFail( newConnection ) ;

	cout	<< "ConnectionManager::finishAccept> Failed to set "
		<< "socket options for connection: "
		<< *newConnection
		<< endl ;

	// Close the socket associated with this connection
	closeSocket( newConnection->getSockFD() ) ;

	// Clean up
	delete newConnection ; newConnection = 0 ;

	// Return error
	return false ;
	}

// Attempt to insert the new Connection into the appropriate
// connectionMap for its handler
if( !handlerMap[ hPtr ].insert( connectionMapType::value_type(
	newConnection, newConnection ) ).second )
	{
	// Failed to insert into handlerMap
	// Notify the handler of a failure in connection
	hPtr->OnConnectFail( newConnection ) ;

	cout	<< "ConnectionManager::finishAccept> Failed to add "
		<< "new connection to table: "
		<< *newConnection
		<< endl ;

	// Socket is valid, but something went wrong with the
	// insertion...make sure to close the socket.
	closeSocket( newConnection->getSockFD() ) ;

	// Clean up memory
	delete newConnection ; newConnection = 0 ;

	// Return error
	return false ;
	}

// Notify the responsible handler of the new incoming connection
hPtr->OnConnect( newConnection ) ;

// Return success
return true ;
}

/**
 * Attempt to set all options for the given socket.
 * If we encounter an error, return false, and let the
 * calling method decide what to do with the socket.
 */
bool ConnectionManager::setSocketOptions( int sockFD )
{

// Set to non-blocking
int optval = ::fcntl( sockFD, F_GETFL, 0 ) ;
if( optval < 0 )
	{
	return false ;
	}

optval = ::fcntl( sockFD, F_SETFL, optval | O_NONBLOCK ) ;
if( optval < 0 )
	{
	return false ;
	}

// Detect closed connection
optval = ::setsockopt( sockFD, SOL_SOCKET, SO_KEEPALIVE,
	reinterpret_cast< const char* >( &optval ), sizeof( optval ) ) ;
if( optval < 0 )
	{
	return false ;
        }

// Disable linger
struct linger setLinger ;
setLinger.l_onoff = 0 ;
setLinger.l_linger = 0 ;

optval = ::setsockopt( sockFD, SOL_SOCKET, SO_LINGER,
	reinterpret_cast< const char* >( &setLinger ),
	sizeof( setLinger ) ) ;
if( optval < 0 )
	{
	return false ;
	}

return true ;
}

void ConnectionManager::Write( const ConnectionHandler* hPtr,
	Connection* cPtr, const string& msg )
{
// Public method, check method arguments
assert( hPtr != 0 ) ;
assert( cPtr != 0 ) ;

// Do nothing if the output message is empty, or the socket
// is a listening socket (not connected anyway).
if( msg.empty() || cPtr->isListening() )
	{
	return ;
	}

// Append the outgoing data onto the Connection's output buffer
cPtr->outputBuffer += msg ;
}

void ConnectionManager::Write( const ConnectionHandler* hPtr,
	Connection* cPtr, const stringstream& msg )
{
// Public method, check method arguments
assert( hPtr != 0 ) ;
assert( cPtr != 0 ) ;

// Do nothing if the socket is a listening socket (not connected)
if( cPtr->isListening() )
	{
	return ;
	}

// Append the outgoing data onto the Connection's output buffer
cPtr->outputBuffer += msg.str() ;
}

const Connection* ConnectionManager::Listen( ConnectionHandler* hPtr,
	const unsigned short int port )
{
// Public method, check arguments
assert( hPtr != 0 ) ;

cout	<< "ConnectionManager::List> Port: "
	<< port
	<< endl ;

// Attempt to open a socket
// openSocket() will also call setSocketOptions()
int listenFD = openSocket() ;
if( listenFD < 0 )
	{
	cout	<< "ConnectionManager::Listen> Failed to open socket"
		<< endl ;
	return 0 ;
	}

// setSocketOptions() does not set SO_REUSEADDR.
// However, for server sockets, it's important to set SO_REUSEADDR,
// to allow fast rebinds.
int optVal = 0 ;
if( ::setsockopt( listenFD, SOL_SOCKET, SO_REUSEADDR,
	reinterpret_cast< const char* >( &optVal ),
	sizeof( optVal ) ) < 0 )
	{
	// Failed to set SO_REUSEADDR
	cout	<< "ConnectionManager::Listen> Failed to set "
		<< "SO_REUSEADDR: "
		<< strerror( errno )
		<< endl ;

	// Close the socket
	closeSocket( listenFD ) ;

	// Return failure
	return 0 ;
	}

// Create and configure a new Connection
Connection* newConnection = new (std::nothrow) Connection( delimiter ) ;
assert( newConnection != 0 ) ;

newConnection->setSockFD( listenFD ) ;
newConnection->setListen() ;
newConnection->setPending() ;
newConnection->setTCP() ;
newConnection->setPort( port ) ;
// Leave hostname/IP empty for the new Connection.  This will
// distinguish the connection more easily for use in
// DisconnectByHost() and DisconnectByIP()

// Setup the sockaddr structure
struct sockaddr_in* addr = newConnection->getAddr() ;
addr->sin_family = AF_INET ;
addr->sin_port = htons( static_cast< u_short >( port ) ) ;

// Attempt to bind to the given port
if( ::bind( listenFD,
	reinterpret_cast< sockaddr* >( newConnection->getAddr() ),
	static_cast< socklen_t >( sizeof( struct sockaddr ) ) ) < 0 )
	{
	// bind() failed
	cout	<< "ConnectionManager::Listen> bind() failed: "
		<< strerror( errno )
		<< endl ;

	// Close the socket
	closeSocket( listenFD ) ;

	// Clean up memory area
	delete newConnection ; newConnection = 0 ;

	// Return failure
	return 0 ;
	}

// Attempt to establish listener on the given socket
if( ::listen( listenFD, 5 ) < 0 )
	{
	// listen() failed
	cout	<< "ConnectionManager::Listen> listen() failed: "
		<< strerror( errno )
		<< endl ;

	// Close the socket
	closeSocket( listenFD ) ;

	// Clean up memory
	delete newConnection ; newConnection = 0 ;

	// Return error
	return 0 ;
	}

// Attempt to add this new connection into the handler map for
// the given handler
bool status = handlerMap[ hPtr ].insert( connectionMapType::value_type(
	newConnection, newConnection ) ).second ;
if( !status )
	{
	// Addition to handlerMap failed :(
	cout	<< "ConnectionManager::Listen> Failed to add new "
		<< "connection to handlerMap: "
		<< *newConnection
		<< endl ;

	// Close the socket
	closeSocket( listenFD ) ;

	// Clean up memory
	delete newConnection ; newConnection = 0 ;

	// Return error
	return 0 ;
	}

// There is no need to call accept() once here, as we did
// with connect(), because the Poll() loop will work properly
// without it.

return newConnection ;
}

void ConnectionManager::scheduleErasure( ConnectionHandler* hPtr,
	connectionMapType::iterator connectionItr )
{
// Protected member, no error checking performed on arguments
eraseMapType::iterator eraseItr = eraseMap.find( hPtr ) ;

// Walk through the container
// Continue walking until we find the duplicate (in which case
// return from this method), we encounter the end of the eraseMap,
// or we are no longer examining the connections for the given
// handler (we can do this because a multimap guarantees its
// entries to be kept in a strict weak order)
for( ; (eraseItr != eraseMap.end()) && (eraseItr->first == hPtr) ;
	++eraseItr )
	{
	if( eraseItr->second == connectionItr )
		{
		// Found a duplicate
		// No need to perform any further processing,
		// this connection is already scheduled for
		// erasure and will be removed on the next call
		// to Poll() (assuming this method isn't already
		// being called from Poll() <G>)
		return ;
		}
	} // while()

// The connectionItr is not present in the eraseMap, go ahead
// and add it to the eraseMap to be erased by Poll()
eraseMap.insert( eraseMapType::value_type( hPtr, connectionItr ) ) ;
}