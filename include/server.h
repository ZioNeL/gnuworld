/* server.h
 * This is the header file for the server itself.
 * This class originally created by Orlando Bassotto.
 */

/* Command Map Description
 * -----------------------
 * Command messages read from the network are in the
 * form of characters and character strings.  Messages
 * are handled by passing the message and its arguments
 * to handler functions.
 * Command handler function names are all preceeded
 * with: MSG_
 * Pointers to offsets of these functions within the
 * global variable xServer* Server are stored in a
 * VectorTrie (see web page).
 */

#ifndef __XSERVER_H
#define __XSERVER_H "$Id: server.h,v 1.26 2001/01/28 19:27:35 dan_karrels Exp $"

#include	<string>
#include	<vector>
#include	<list>
#include	<strstream>
#include	<map>
#include	<hash_map>
#include	<queue>
#include	<algorithm>

#include	<ctime>

#include	"Numeric.h"
#include	"iServer.h"
#include	"iClient.h"
#include	"Socket.h"
#include	"ClientSocket.h"
#include	"Buffer.h"
#include	"events.h"
#include	"Gline.h"
#include	"xparameters.h"
#include	"misc.h"
#include	"moduleLoader.h"
#include	"ELog.h"
#include	"TimerHandler.h"

namespace gnuworld
{

/**
 * This macro constructs a method prototype for a command
 * handler with the given name MSG_handlerFunc.
 */
#define DECLARE_MSG( handlerFunc ) \
 virtual int MSG_##handlerFunc( xParameters& ) ;

/**
 * This method registers a command handler with the xServer's
 * command table.  It must first be prototyped in the xServer
 * class declaration.
 */
#define REGISTER_MSG( key, handlerFunc ) \
  if( !commandMap->insert( commandMapType::value_type( key, \
	&xServer::MSG_##handlerFunc ) ).second ) \
	{\
	elog << "Unable to register function: "\
		<< key << std::endl ;\
	exit( 0 ) ; \
	}

/// Forward declaration of xClient
class xClient ;
 
enum MessageType
	{
	SRV_SUCCESS, // all ok
	SRV_RELOAD, // reload request
	SRV_QUIT, // server shutdown
	SRV_DISCONNECT // server disconnected
	} ;

using std::string ;
using std::list ;
using std::vector ;
using std::strstream ;
using std::hash_map ;
using std::priority_queue ;
using std::map ;

/**
 * This class is the server proper; it is responsible for the connection
 * to the IRC network, and for maintaining the services clients.
 */
class xServer
{

protected:

	/**
	 * The type used to store server numerics for juped
	 * servers.
	 */
	typedef vector< unsigned int > jupedServerListType ;
 
public:

	xServer( int, char** ) ;

	/**
	 * Destroy the server and its clients, disconnect
	 * from network.
	 */
	virtual ~xServer() ;

	void		run() ;

	/**
	 * This type is used for passing information to handler
	 * methods for channel op mode changes.
	 */
	typedef vector< pair< bool, ChannelUser* > > opVectorType ;

	/**
	 * This type is used for passing information to handler
	 * methods for channel voice mode changes.
	 */
	typedef opVectorType voiceVectorType ;

	/**
	 * This type is used for passing information to handler
	 * methods for channel ban changes.
	 */
	typedef vector< pair< bool, string > > banVectorType ;

	/**
	 * Connect to a network uplink of the given address
	 * (IP or hostname) and on the given port.
	 */
	virtual int Connect( const string& Address, int Port ) ;

	/**
	 * Connect to the default uplink and port.
	 */
	virtual int Connect()
		{ return Connect( UplinkName, Port ) ; }

	/**
	 * Call this method when a read/write error occurs on the
	 * uplink socket.  This will close and deallocate the socket,
	 * as well as clear the input/output buffers and post a
	 * message for GetMessage() later.
	 */
	virtual void OnDisConnect() ;

	/**
	 * Attach a fake server to this services server.
	 */
	virtual bool AttachServer( iServer*, const string& = "Juped Server" ) ;

	/**
	 * Squit a server from the network and remove it
	 * from the network tables.
	 */
	virtual bool SquitServer( const string& name, const string& reason ) ;

	/* I/O stuff */

	/**
	 * Perform the physical read of the socket.
	 */
	virtual void DoRead() ;

	virtual void DoWrite() ;

	/**
	 * Append a std::string to the output buffer.
	 */
	virtual bool Write( const string& ) ;

	/**
	 * Append a C variable argument list/character array to the output
	 * buffer.
	 */
	virtual bool Write( const char*, ... ) ;

	/**
	 * Append a std::strstream to the output buffer.
	 */
	virtual bool Write( strstream& ) ;

	/**
	 * Write any bufferred data to the network.
	 * Returns false on write error.
	 */
	virtual inline bool flushBuffer() ;

	/**
	 * Read a '\n' delimited line from the input buffer.
	 * Return true is none exist.  (size) is the length of
	 * the C string buffer (buf).
	 */
	virtual inline bool GetString( char* buf ) ;

	/**
	 * Return true if a read attempt from the network
	 * would NOT block.
	 * This method is not const beause it may modify
	 * _connected and Socket if an error occurs.
	 */
	virtual inline bool ReadyForRead() ;

	/**
	 * Return true if data exists to be written to the
	 * network, and a write would NOT block.
	 */
	virtual inline bool ReadyForWrite() const ;

	/**
	 * Process is responsible for parsing lines of data.
	 */
	virtual void Process( char* String ) ;

	/**
	 * Add a network gline and update glines table.
	 */
	virtual bool setGline( const string& setBy,
		const string& userHost,
		const string& reason,
		const time_t& duration ) ;

	/**
	 * Remove a network gline and update internal gline table.
	 */
	virtual bool removeGline( const string& userHost ) ;

	/**
	 * Find a gline by lexical searching, case insensitive.
	 */
	virtual const Gline* findGline( const string& userHost ) const ;

	/**
	 * Find one or more glines matching a given userHost string.
	 */
	virtual vector< const Gline* > matchGline( const string& userHost ) const ;

	/* Client stuff */

	/**
	 * Attach a client to the server.  This will add the client
	 * to the internal table, and call the client's ImplementServer()
	 * method.
	 */
	virtual bool AttachClient( xClient* Client ) ;

	/**
	 * Attach a fake client to a fake (juped) server.
	 * The server must exist and must already be attached
	 * to this server.
	 */
	virtual bool AttachClient( iClient* Client ) ;

	/**
	 * Detach a client from the server.  This will call the
	 * client's Exit() method and remove the client from the
	 * internal tables.
	 */
	virtual bool DetachClient( const string& Nick ) ;

	/**
	 * Detach a client from the server.  This will call the
	 * client's Exit() method and remove the client from the
	 * internal tables.
	 */
	virtual bool DetachClient( xClient* Client ) ;

	/**
	 * Output the information for a channel, and make the given
	 * xClient operator in that channel.
	 * This works at all times, bursting or not.
	 */
	virtual void JoinChannel( xClient*, const string& chanName,
		const string& chanModes = "+tn",
		const time_t& joinTime = 0,
		bool getOps = true ) ;

	/**
	 * Notify the network that one of the services clients has
	 * parted a channel.
	 */
	virtual void PartChannel( xClient* theClient, const string& chanName ) ;

	/**
	 * Notify the network that one of the services clients has
	 * parted a channel.
	 */
	virtual void PartChannel( xClient* theClient, Channel* theChan ) ;

	/**
 	 * Handle the parting of a services client from a channel.  This
	 * method updates internal tables.
 	 */
	virtual void OnPartChannel( xClient* theClient, const string& chanName ) ;

	/**
 	 * Handle the parting of a services client from a channel.  This
	 * method updates internal tables.
 	 */
	virtual void OnPartChannel( xClient* theClient, Channel* theChan ) ;

	/**
	 * Handle the parting of a network client from a channel.  This method
	 * updates internal tables.
	 */
	virtual void OnPartChannel( iClient* theClient, const string& chanName ) ;

	/**
	 * Handle the parting of a network client from a channel.  This method
	 * updates internal tables.
	 */
	virtual void OnPartChannel( iClient* theClient, Channel* theChan ) ;

	/**
	 * Output the information about an xClient to the network.
	 * (localClient) is true when the xClient is to appear to
	 * reside on this xServer, false when it is to reside on
	 * a juped/fake server.
	 */
	virtual void BurstClient( xClient*, bool localClient = true ) ;

	/**
	 * Change channel modes as the server.
	 * This method also updates internal tables.
	 */
	virtual void SetChannelMode( Channel* theChan, const string& theModes ) ;

	/* Event registration stuff */

	/**
	 * RegisterEvent is called by xClient's wishing
	 * to receive a particular event.
	 * When a particular event occurs, the server will call
	 * OnEvent for each xClient registered to receive that
	 * event.
	 */
	virtual bool RegisterEvent( const eventType&, xClient* ) ;

	/**
	 * Halt delivery of the given event to the given xClient.
	 */
	virtual bool UnRegisterEvent( const eventType&, xClient* ) ;

	/**
	 * The channel event distribution system is rather
	 * expensive...such is the nature of IRC.
	 * Each channel name is converted to lower case.
	 * When a channel event occurs, the server will call
	 * each OnChannelEvent() with the event type
	 * and channel name for each xClient registered for
	 * that <event,channel> pair.
	 */
	virtual bool RegisterChannelEvent( const string&,
		xClient* ) ;

	/**
	 * Halt delivery of any channel event for the particular channel
	 * to the particular xClient.
	 */
	virtual bool UnRegisterChannelEvent( const string&,
		xClient* ) ;

	/**
	 * The type used to represent client timer events.
	 */
	typedef TimerHandler::timerID timerID ;

	/**
	 * Register for a timer event.  The first argument is the
	 * absolute time at which the timed event is to occur.
	 * The second argument is a pointer to an argument to be
	 * passed to the timer handler.
	 * Returns 0 on failure, a valid timerID otherwise.
	 */
	virtual timerID RegisterTimer( const time_t& absoluteTime,
		TimerHandler* theHandler,
		void* data = 0 ) ;

	/**
	 * Remove a timed event from the timer system.
	 * If data is non-NULL, the timer argument passed to
	 * RegisterTimer() will be returned through data.
	 * Return true if successful, false otherwise.
	 */
	virtual bool	UnRegisterTimer( const timerID&, void*& data ) ;

	/**
	 * Post a system event to the rest of the system.  Note
	 * that this method is public, so xClients may post
	 * events.
	 */
	virtual void PostEvent( const eventType&,
		void* = 0, void* = 0, void* = 0, void* = 0 ) ;

	/**
	 * Post a channel event to the rest of the system.  Note
	 * that this method is public, so xClients may post
	 * channel events.
	 */
	virtual void PostChannelEvent( const channelEventType&,
		Channel* theChan,
		void* = 0, void* = 0, void* = 0, void* = 0 ) ;

	/**
	 * This variable represents "all channels."  Clients may
	 * register for events of this channel, and each will receive
	 * this event for every channel in existence on the network.
	 */
	const static string	CHANNEL_ALL ;

	/**
	 * Post a signal to the server and all clients.
	 * Returns true if the signal was handled, false
	 * otherwise.
	 */
	virtual bool	PostSignal( int ) ;

	/*
	 * Server message system
	 * The message system is used for communicating with
	 * main() any server critical messages, such as a
	 * disconnect on error.
	 */

	/**
	 * Post a server message for the world to see.
	 */
	virtual void PostMessage( MessageType Msg )
		{ Message = Msg ; }

	/**
	 * Return true if a message has been posted.
	 */
	virtual bool MessageReady() const
		{ return (Message != SRV_SUCCESS) ; }

	/**
	 * Retrieve a message.  Returns -1 if no message ready.
	 */
	virtual MessageType GetMessage()
		{ return Message ; }

	/**
	 * Once a message has been received, call this method to
	 * make sure that the internal state is updated.
	 */
	virtual void ResetMessage()
		{ Message = SRV_SUCCESS ; }

	/* Utility methods */

	/**
	 * Return true if no BURST state exists, false otherwise.
	 */
	virtual bool IsEndOfBurst() const
		{ return !bursting ; }

	/**
	 * Return true if the server has a valid connection to
	 * its uplink, false otherwise.
	 */
	virtual bool isConnected() const
		{ return _connected ; }

	/* Numeric utility methods */

	/**
	 * Return an unsigned int representation of this server's
	 * numeric server numeric.
	 */
	inline const unsigned int& getIntYY() const
		{ return intYY ; }

	/**
	 * Return an unsigned int representation of this server's
	 * maximum number of possible clients.
 	 */
	inline const unsigned int& getIntXXX() const
		{ return intXXX ; }

	/**
	 * Return a character array representation of this server's
	 * server numeric, base64.
	 */
	inline const char* getCharYY() const
		{ return charYY ; }

	/**
	 * Return a character array representation of this server's
	 * maximum number of possible clients, base 64.
	 */
	inline const char* getCharXXX() const
		{ return charXXX ; }

	/**
	 * Return an unsigned int representation of this server's uplink's
	 * server numeric.
	 */
	inline const unsigned int& getUplinkIntYY() const
		{ return Uplink->getIntYY() ; }

	/**
	 * Return a std::string representation of this server's full
	 * numeric, base64.
	 */
	inline const string getCharYYXXX() const
		{ return( string( charYY ) + charXXX ) ; }

	/* General server utility methods */

	/**
	 * Return this server's name, as the network sees it.
	 */
	inline const string& getName() const
		{ return ServerName ; }

	/**
	 * Return a description of this server.
	 */
	inline const string& getDescription() const
		{ return ServerDescription ; }

	/**
	 * Return this server's uplink password.
	 */
	inline const string& getPassword() const
		{ return Password ; }

	/**
	 * Return the time at which this server was instantiated.
	 */
	inline const time_t& getStartTime() const
		{ return StartTime ; }

	/**
	 * Return the time this server last connected to its uplink.
	 */
	inline const time_t& getConnectionTime() const
		{ return ConnectionTime ; }

	/**
	 * This is a simple mutator of the server's socket pointer.
	 * This is used ONLY for implementing the simulation mode.
	 */
	inline void setSocket( ClientSocket* newSock )
		{ theSock = newSock ; }

	/**
	 * Shutdown the server.
	 */
	virtual void Shutdown() ;

	/**
	 * Output server statistics to the console (clog).
	 */
	virtual void dumpStats() ;

	/**
	 * Execute any waiting client timers.
	 * Return the number of timers executed.
	 */
	virtual unsigned int CheckTimers() ;

	/**
	 * The main loop which runs the server.  This contains
	 * all of the server essential logic.
	 */
	void		mainLoop() ;

	/**
	 * This method is called when a channel mode 't' change is
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 * detected.
	 */
	virtual void	onChannelModeT( Channel*, bool, ChannelUser* ) ;

	/**
	 * This method is called when a channel mode 'n' change is
	 * detected.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeN( Channel*, bool, ChannelUser* ) ;

	/**
	 * This method is called when a channel mode 's' change is
	 * detected.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeS( Channel*, bool, ChannelUser* ) ;

	/**
	 * This method is called when a channel mode 'p' change is
	 * detected.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeP( Channel*, bool, ChannelUser* ) ;

	/**
	 * This method is called when a channel mode 'm' change is
	 * detected.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeM( Channel*, bool, ChannelUser* ) ;

	/**
	 * This method is called when a channel mode 'i' change is
	 * detected.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeI( Channel*, bool, ChannelUser* ) ;

	/**
	 * This method is called when a channel mode 'l' change is
	 * detected.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeL( Channel*, bool,
				ChannelUser*, unsigned int ) ;

	/**
	 * This method is called when a channel mode 'k' change is
	 * detected.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeK( Channel*, bool,
				ChannelUser*, const string& ) ;

	/**
	 * This method is called when one or more mode 'o' changes
	 * are set/unset on a particular channel.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeO( Channel*, ChannelUser*,
		const opVectorType& ) ;

	/**
	 * This method is called when one or more mode 'v' changes
	 * are set/unset on a particular channel.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeV( Channel*, ChannelUser*,
		const voiceVectorType& ) ;

	/**
	 * This method is called when one or more mode 'b' changes
	 * are set/unset on a particular channel.
	 * Keep in mind that the source ChannelUser may be NULL
	 * if the mode is being set/unset by a server.
	 */
	virtual void	onChannelModeB( Channel*, ChannelUser*,
		const banVectorType& ) ;

	/**
	 * Check the list of glines for any that are about to
	 * expire.
	 */
	virtual void updateGlines() ;

protected:

	/**
	 * Allow only subclasses to call the default
	 * constructor.
	 */
	xServer() {}

	/**
	 * Disable copy constructor, this method is declared but NOT defined.
	 */
	xServer( const xServer& ) ;

	/**
	 * Disable assignment, this method is declared but NOT defined.
	 */
	xServer operator=( const xServer& ) ;

	/**
	 * Burst out information about all xClients on this server.
	 */
	virtual void BurstClients() ;

	/**
	 * Output channel information for each client on this server.
	 */
	virtual void BurstChannels() ;

	/**
	 * Remove all modes from a channel, used when bursting an
	 * older timestamp into a channel.
	 */
	virtual void	removeAllChanModes( Channel* ) ;

	/**
	 * Parse a burst line for channel bans.
	 */
	virtual void parseBurstBans( Channel*, const char* ) ;

	/**
	 * Parse a burst line for channel users.
	 */
	virtual void parseBurstUsers( Channel*, const char* ) ;

	/**
	 * Convenience method that will part a given network
	 * client from all channels, and notify each listening
	 * xClient of the parts.
	 */
	virtual void userPartAllChannels( iClient* ) ;

	/**
	 * Read the config file.  Return true if success, false
	 * otherwise.
	 */
	virtual bool readConfigFile( const string& ) ;

	/**
	 * Parses a config file and attempts to load all modules
	 * specified therein.  If any part of the process fails,
	 * false is returned.  Otherwise, true is returned.
	 */
	virtual bool loadModules( const string& ) ;

	/**
	 * Signal handler for the server itself.
	 * Returns true if the signal was handled.
	 */
	virtual bool	OnSignal( int ) ;

	/**
	 * This method is called when a user mode change is detected.
	 */
	virtual void	onUserModeChange( xParameters& ) ;

	/**
	 * This variable represents how many times to attempt a system
	 * call before giving up
	 */
	unsigned int	maxLoopCount ;

	static bool		caughtSignal ;
	static int		whichSig ;

	/**
	 * The structure type to hold information about client timed
	 * events.
	 */
	struct timerInfo
	{
	timerInfo( const timerID& _ID,
		const time_t& _absTime,
		TimerHandler* _theHandler,
		void* _data = 0 )
	: ID( _ID ),
	  absTime( _absTime ),
	  theHandler( _theHandler ),
	  data( _data )
	{}

		timerID		ID ;
		time_t		absTime ;
		TimerHandler*	theHandler ;
		void*		data ;
	} ;

	/**
	 * This structure is used as a comparator functor for
	 * the timerQueue.
	 */
	struct timerGreater
	{
	inline bool operator()( const pair< time_t, timerInfo* >& lhs,
		const pair< time_t, timerInfo* >& rhs ) const
		{
		return lhs.first > rhs.first ;
		}
	} ;

	/**
	 * Register the timers that the server uses.
	 */
	virtual void		registerServerTimers() ;

	/**
	 * Return a unique timerID.
	 */
	virtual timerID		getUniqueTimerID() ;

	/* Network message handlers */

	/// ERROR message handler, deprecated.
	DECLARE_MSG(Error);

	/// RPING message handler, deprecated.
	DECLARE_MSG(RemPing);

	/// P(RIVMSG) message handler.
	DECLARE_MSG(P);

	/// B(URST) message handler.
	DECLARE_MSG(B);

	/// EA (End of burst Acknowledge) message handler.
	DECLARE_MSG(EA);

	/// EB (End of BURST) message handler.
	DECLARE_MSG(EB);

	/// G(PING) message handler.
	DECLARE_MSG(G);

	/// J(OIN) message handler.
	DECLARE_MSG(J);

	/// C(REATE) message handler.
	DECLARE_MSG(C);

	/// L(EAVE) message handler.
	DECLARE_MSG(L);

	/// PART message handler, non-tokenized, bogus
	DECLARE_MSG(PART);

	/// M(ODE) message handler.
	DECLARE_MSG(M);

	/// N(ICK) message handler.
	DECLARE_MSG(N);

	/// Q(UIT) message handler.
	DECLARE_MSG(Q);

	/// S(ERVER) message handler.
	DECLARE_MSG(S);

	/// SERVER message handler, deprecated.
	DECLARE_MSG(Server);

	/// SQ(UIT) message handler.
	DECLARE_MSG(SQ);

	/// D(KILL) message handler.
	DECLARE_MSG(D);

	/// WA(LLOPS) message handler.
	DECLARE_MSG(WA);

	// STATS message handler.
	DECLARE_MSG(R);

	/// PASS message handler.
	DECLARE_MSG(PASS);

	/// GL(INE) message handler
	DECLARE_MSG(GL);

	/// T(OPIC) message handler.
	DECLARE_MSG(T);

	/// K(ICK) message handler.
	DECLARE_MSG(K);

	// DE(SYNCH) ?
	DECLARE_MSG(DS);

	// AD(MIN)
	DECLARE_MSG(AD);

	/// NOOP message.
	/// Use this handler for any messages that we don't need to handle.
	/// Included for completeness.
	DECLARE_MSG(NOOP);

	// Non-tokenized command handlers
	// Replication of code *sigh*

	/**
	 * Bounds checker for events.
	 */
	inline bool validEvent( const eventType& theEvent ) const
		{ return (theEvent >= 0 && theEvent < EVT_NOOP) ; }

	/**
	 * This is the command map type.  Pointers to
	 * the bound offset of the command handler methods
	 * are stored in this structure.
	 */
	typedef hash_map< string, int (xServer::*)( xParameters& ),
		eHash, eqstr > commandMapType ;

	/**
	 * A pointer to the server command handler.
	 */
	commandMapType		*commandMap ;	

	/**
	 * This points to the input/output stream to be used for
	 * server->server communication.  This may point to an
	 * instance of FileSocket if the server is running in
	 * simulation mode.
	 */
	ClientSocket		*theSock ;

	/**
	 * The name of the server, as the network sees it.
	 */
	string			ServerName ;

	/**
	 * This server's description line.
	 */
	string			ServerDescription ;

	/**
	 * The password for our uplink server.
	 */
	string			Password ;

	/**
	 * The hostname/IP of our uplink
	 */
	string			UplinkName ;

	/**
	 * This vector holds the server numerics of any servers
	 * that we are juping.  The actual iServer instances
	 * are maintained by the xNetwork instance, Network.
	 */
	jupedServerListType	jupedServers ;

	/**
	 * The type used to store the system event map.
	 */
	typedef vector< list< xClient* > > eventListType ;

	/**
	 * This is the vector of lists of xClient pointers.
	 * When clients register to receive an event, that xClient's
	 * pointer is added to eventListType[ theEvent ].
	 * When an event of that type occurs, each xClient in the
	 * list is called (OnEvent()).
	 */
	eventListType		eventList ;

	/**
	 * Type used to store the channel event map.
	 */
	typedef hash_map< string, list< xClient* >*, eHash, eqstr >
		channelEventMapType ;

	/**
	 * This structure provides a nice iterator interface, and
	 * runs in O(logn) time.  This should probably be moved
	 * to some form of a hashtable, though it will have to
	 * be specially built to meet the server's needs.
	 * Any volunteers? :)
	 */
	channelEventMapType	channelEventMap ;

	/**
	 * The type of the structure to hold Gline's internally.
	 */
	typedef list< Gline* >	glineListType ;

	/**
	 * This structure holds the current network glines.
	 */
	glineListType		glineList ;

	/**
	 * This is the time this xServer was instantiated.
	 */
	time_t 			StartTime ;

	/**
	 * This is the time that we last connected to our uplink.
	 */
	time_t			ConnectionTime ;

	/**
	 * Time at which we began the last burst.
	 */
	time_t			burstStart ;

	/**
	 * Time at which we ended the last burst.
	 */
	time_t			burstEnd ;

	/**
	 * This is the version of the xServer, pretty useless.
	 */
	long			Version ;

	/**
	 * This variable is true when this server is bursting.
	 */
	bool			bursting ;

	/**
	 * This variable is true when the socket connection is valid.
	 */
	bool			_connected ;

	volatile bool		keepRunning ;

	/**
	 * This is the current message error number, or -1 if no
	 * error exists.
	 */
	MessageType		Message ;

	/**
	 * This is the port number to which we connect on our uplink.
	 */
	int			Port ;

	/**
	 * This is the unsigned integer representation of our server numeric.
	 */
	unsigned int		intYY ;

	/**
	 * This is the unsigned integer representation of the max number
	 * of clients we can accept.
	 */
	unsigned int		intXXX ;

	/**
 	 * This is the base 64 character array representation of this server's
	 * numeric.
	 */
	char			charYY[ 3 ] ;

	/**
	 * This is the base 64 character array representation of this
	 * server's maximum number of allowable clients.
	 */
	char			charXXX[ 4 ] ;

	/**
	 * This is a pointer into the network table to our uplink
	 * server.  It is kept here for convenience.
	 */
	iServer* 		Uplink ;

	/**
	 * This is the buffer into which network commands are read
	 * and from which they are later processed.
	 */
	Buffer< char >		inputBuffer ;

	/**
	 * This is the output buffer from which data is written to
	 * the network.
	 */
	Buffer< char >		outputBuffer ;

	/**
	 * This is the size of the TCP input window.
	 */
	size_t			inputReadSize ;

	/**
	 * This is the size of the TCP output window.
	 */
	size_t			outputWriteSize ;

	/**
	 * Burst() is called when the network connection is
	 * established.  Its purpose is to call each xClient's
	 * Connect() method so that each client may burst itself
	 * and its channels.
	 * NOTE: The scope of this method will be altered in
	 * the future to reduce the requirements of xClient
	 * when bursting its information.
	 */
	void 			Burst() ;

	/**
	 * List used to store runtime modules.
	 */
	typedef vector< moduleLoader< xClient* >* >	moduleListType;
	moduleListType		moduleList;

	typedef priority_queue< pair< time_t, timerInfo* >,
		vector< pair< time_t, timerInfo* > >,
		timerGreater >
		timerQueueType ;
	timerQueueType  timerQueue ;

	typedef map< timerID, bool > uniqueTimerMapType ;
	uniqueTimerMapType		uniqueTimerMap ;

	timerID		lastTimerID ;

#ifdef LOG_SOCKET
	ofstream	socketFile ;
#endif

#ifdef EDEBUG
	string		elogFileName ;
#endif

	string		configFileName ;
	char*		inputCharBuffer ;
	bool		verbose ;

	static void	sigHandler( int ) ;
	void		initializeSystem() ;
	void		initializeVariables() ;
	void		loadCommandHandlers() ;
	bool		setupSignals() ;
} ;

} // namespace gnuworld

#endif // __XSERVER_H
