/**
 * ConnectionManager.h
 * Author: Daniel Karrels (dan@karrels.com)
 * $Id: ConnectionManager.h,v 1.1 2002/05/27 17:22:02 dan_karrels Exp $
 */

#ifndef __CONNECTIONMANAGER_H
#define __CONNECTIONMANAGER_H "$Id: ConnectionManager.h,v 1.1 2002/05/27 17:22:02 dan_karrels Exp $"

#include	<sys/types.h>

#include	<iostream>
#include	<sstream>
#include	<string>
#include	<list>
#include	<map>

#include	<ctime>

#include	"Connection.h"
#include	"ConnectionHandler.h"

#include	"defs.h"

#ifdef GNU_EXTENSIONS
 #include       <ext/hash_map>
#else
 #include       <hash_map>
#endif

using std::stringstream ;
using std::multimap ;
using std::string ;
using std::map ;
using HASHMAPNS::hash_map ;

/**
 * The purpose of this class it to manage multiple incoming and
 * outgoing connections on behalf of ConnectionHandler's.  This
 * class is intended for systems which support multiple client
 * classes which might require one or more incoming and outgoing
 * connections.  Any client who wishes to create a connection
 * should subclass ConnectionHandler, and overload the method(s)
 * in which it is interested.
 * This class will support all connections for any number of
 * different ConnectionHandlers (note that a pointer to the
 * ConnectionHandler is passed as the first argument to many
 * methods).  Each Connection is associated with a particular
 * ConnectionHandler, and no other ConnectionHandlers may view
 * or modify Connections which it does not own.
 * Any opening/closing of Connections is performed within this
 * class, so it is not necessary to perform any direct maintenance
 * of a particular Connection.  Simply remember to call the
 * appropriate methods based on different situations (Disconnect(),
 * for example), and the ConnectionManager will update the state
 * of those Connections.
 */
class ConnectionManager
{

	/**
	 * This is a generic little hashing functor.  It will be
	 * used to hash key's of type Connection*.  Since this
	 * is essentially an integer, and all pointers to different
	 * value objects are unique, there is no need for any
	 * special hashing function -- the pointer is simply
	 * typecast to an int and returned.
	 */
	struct cmHash
	{
	inline size_t operator()( const Connection* cPtr ) const
		{
		return reinterpret_cast< size_t >( cPtr ) ;
		}
	} ;

	/**
	 * This type is used to store Connection's in a weak sorted
	 * manner.
	 * There is a single instance of a connectionMapType for
	 * each handler which has one or more Connection's registered.
	 * TODO: Change this to something other than a hash_map.
	 */
	typedef hash_map< Connection*, Connection*, cmHash >
		connectionMapType ;

	/**
	 * This map stores connectionMapType's, keyed by the handler
	 * which registered the connection(s).
	 */
	typedef map< ConnectionHandler*, connectionMapType > 
		handlerMapType ;

	/**
	 * The type used to store Connection objects to be erased.
	 * This structure stores an iterator to each Connection
	 * to be removed.  Removal is synchronous to prevent
	 * iterator invalidation of the handlerMap.
	 * Because more than one item may be associated with any
	 * given key, we need a multimap here.  While that may
	 * be a useful trait for handling more than one Connection
	 * for any given ConnectionHandler, it also has the unfortunate
	 * side effect of allowing a Connection to be scheduled for
	 * closure more than once.  The scheduleErasure() method is
	 * used to prevent multiple entries of the same Connection
	 * into the eraseMap.
	 */
	typedef multimap< ConnectionHandler*, connectionMapType::iterator >
		eraseMapType ;

public:
	/**
	 * Default constructor.  The first argument which (may) be
	 * supplied is the default timeout value for establishing
	 * individual connections (in seconds).  If the (outgoing)
	 * connection is not established within that time period,
	 * then the connection's handler is notified via OnTimeout(),
	 * and the Connection scheduled for erasure.  Note that
	 * listening Connections do not have a timeout.
	 * Delimiter is the line delimiter for determining when a
	 * full line/command has been read from each connection.
	 * Once this delimiter is encountered, the line/command is
	 * passed to OnRead().
	 * Setting the delimiter to 0 ('\0') will cause all data
	 * read from the connection to be delivered immediately
	 * via OnRead(). TODO: test this
	 */
	ConnectionManager( const time_t defaultTimeout = 10,
		const char defaultDelimiter = '\n' ) ;

	/**
	 * The destructor will deallocate any memory and close all
	 * connections.
	 * Handlers for the given connections will *not* be
	 * notified.
	 */
	virtual ~ConnectionManager() ;

	/**
	 * This method will set the timeout for connection attempts
	 * to the new value given to the method.
	 */
	void		setTimeout( const time_t newTimeout )
				{ timeout = newTimeout ; }

	/**
	 * Return a string with (host)'s IP address in numbers
	 * and dots format.
	 * Returns an empty string if no IP address found.
	 */
	static string	ipAddrOf( const string& host ) ;

	/**
	 * Return true if the given string is in the proper
	 * IP format of numbers and dots.
	 */
	static bool	isIpAddress( const string& host ) ;

	/**
	 * Connect() will attempt to establish a new connection to
	 * the given host, on the given port.  The (host) field may
	 * be the canonical host name, or the IP in the form of
	 * numbres and dots. If TCP is true (or
	 * not given to the method, thus default), then a TCP
	 * connection will be made, UDP otherwise.
	 * This method creates a non-blocking socket with which to
	 * connect to the remote host, thus a return value of non-NULL
	 * does not necessarily mean that the connection is valid,
	 * just that the attempt is in progress.
	 * A return value of NULL indicates that some part of the
	 * connection process failed, and errno is set appropriately.
	 * UDP sockets are currently not implemented fully, and will
	 * not work properly.
	 * The ConnectionHandler must be non-NULL.
	 */
	virtual const Connection*	Connect(
				ConnectionHandler*,
				const string& host,
				unsigned short int port,
				bool TCP = true ) ;

	/**
	 * Attempt to establish a listening Connection on the
	 * given port number.  If successful, the Connection is
	 * returned.  The Connection returned is of no functional
	 * use except to indicate success or failure.  That
	 * Connection is the actual listening socket, and cannot
	 * be written to or read from directly.
	 * The ConnectionHandler must be non-NULL.
	 */
	virtual const Connection*	Listen(
				ConnectionHandler*,
				const unsigned short int port ) ;

	/**
	 * DisConnect() forces the connection associated with
	 * hostname/port to be disconnected and deallocated.
	 * OnDisconnect() is NOT called.
	 * The ConnectionHandler must be non-NULL.
	 * The Connection will not be removed if the ConnectionHandler
	 * does not own the particular Connection.
	 * This method schedules the given Connection to be disconnected
	 * in the next call to Poll().
	 * To close a listening Connection, pass an empty hostname.
	 */
	virtual bool	DisconnectByHost( ConnectionHandler*,
				const string& hostname,
				unsigned short int port ) ;

	/**
	 * DisConnect() forces the connection associated with
	 * IP/port to be disconnected and deallocated.
	 * OnDisconnect() is NOT called.
	 * The ConnectionHandler must be non-NULL.
	 * The Connection will not be removed if the ConnectionHandler
	 * does not own the particular Connection.
	 * This method schedules the given Connection to be disconnected
	 * in the next call to Poll().
	 * To close a listening Connection, pass an empty IP.
	 */
	virtual bool	DisconnectByIP( ConnectionHandler*,
				const string& IP,
				unsigned short int port ) ;

	/**
	 * Disconnect the given Connection from ConnectionHandler's
	 * list of Connections.
	 * The Connection will not be removed if the ConnectionHandler
	 * does not own the particular Connection.
	 * Return true if removal was successful, false if the
	 * Connection was not found under ConnectionHandler's control.
	 * Both the ConnectionHandler and the Connection must
	 * be non-NULL.
	 * This method schedules the given Connection to be disconnected
	 * in the next call to Poll().
	 */
	virtual bool	Disconnect( ConnectionHandler*,
				Connection* ) ;

	/**
	 * Appends data to the given Connection's output buffer,
	 * to be sent during a call to Poll().
	 * ConnectionHandler and Connection must be non-NULL.
	 */
	virtual void	Write( const ConnectionHandler*,
				Connection*, const string& ) ;

	/**
	 * Appends data to the given Connection's output buffer,
	 * to be sent during a call to Poll().
	 * ConnectionHandler and Connection must be non-NULL.
	 */
	virtual void	Write( const ConnectionHandler*,
				Connection*, const stringstream& ) ;

	/**
	 * This method performs the actual read/write calls for all
	 * associated sockets.  This method will check for any
	 * pending outgoing connections (and call OnConnect() for
	 * all that succeed), check for read state on all sockets
	 * which are currently connected (and call OnRead() if conditions
	 * are met), check for dead connections (and call OnDisconnect()
	 * for each), and check for connection time outs (and call
	 * OnTimeout() for each).
	 * (seconds) and (milliseconds) is how long to wait for a
	 * state change on any of the Connections, in seconds and
	 * milliseconds, respectively.  The default is to return
	 * immediately (poll).
	 * If -1 is passed for seconds, then the process will block
	 * indefinitely waiting for a state change.
	 */
	virtual void	Poll( long seconds = 0, long milliseconds = 0 ) ;

protected:

	/// The time to wait for outgoing connections to be established
	time_t		timeout ;

	/// The line delimiter, 0 if none
	char		delimiter ;

	/// Stores connectionMap's, one for each handler (key)
	handlerMapType	handlerMap ;

	/// Allow for asynchronous calls to Disconnect()
	eraseMapType	eraseMap ;

	/// Open a socket: TCP if TCP is true, otherwise UDP
	/// Return -1 on error
	int		openSocket( bool TCP = true ) ;

	/// Close a socket
	void		closeSocket( int ) ;

	/// Set the options for a socket
	/// Return true is all options were set properly, false
	/// otherwise.
	bool		setSocketOptions( int ) ;

	/**
	 * Attempt to read()/recv() from the given Connection.
	 * Post event(s) OnRead() or OnDisconnect().
	 * Return true if the read was successful, false if
	 * connection is no longer valid.
	 */
	bool		handleRead( ConnectionHandler*, Connection* ) ;

	/**
	 * Attempt to write()/send() to the given Connection.
	 * Post event OnDisconnect() if necessary.
	 * Return true if the write was successful, false if
	 * the connection is no longer valid.
	 */
	bool		handleWrite( ConnectionHandler*, Connection* ) ;

	/**
	 * Attempt to complete the connection to the given Connection.
	 * Post event(s) OnConnect() or OnConnectFail().
	 * Return true if connect was successful, false if Connection
	 * is invalid.
	 */
	bool		finishConnect( ConnectionHandler*, Connection* ) ;

	/**
	 * Attempt to complete an incoming connection creation.
	 * The ConnectionHandler will be notified either by a call
	 * to OnConnect() or OnConnectFail(), depending if the incoming
	 * connection attempt was successful or unsuccessful,
	 * respectively.
	 * Return true if connection attempt was successful, false
	 * otherwise.
	 */
	bool		finishAccept( ConnectionHandler*, Connection* ) ;

	/**
	 * Because the eraseMap is a multimap, it is possible to insert
	 * more than one value for each key.  This is useful for
	 * removing more than a single connection for any single handler,
	 * but it also permits the insertion of the same connection
	 * more than once.  This would create a problem when closing
	 * connections, because the second (and third, fourth, etc)
	 * instance of a particular iterator would be invalidated
	 * once the iterator is removed once -- this would cause
	 * a process crash.
	 * This method performs a simple check to see if the connection
	 * iterator is already present in the eraseMap.  If so, just
	 * return because the connection is already scheduled to be
	 * removed, and this will occur in Poll().  Otherwise, add
	 * the connection to be erased to the eraseMap.
	 */
	void		scheduleErasure( ConnectionHandler*,
				connectionMapType::iterator ) ;

} ;

#endif // __CONNECTIONMANAGER_H