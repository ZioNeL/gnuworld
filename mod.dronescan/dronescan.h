#ifndef DRONESCAN_H
#define DRONESCAN_H "$Id: dronescan.h,v 1.5 2003/05/08 11:42:53 jeekay Exp $"

#include <map>

#include "client.h"

#include "clientData.h"
#include "dronescanCommands.h"
#include "dronescanTests.h"
#include "Timer.h"

namespace gnuworld {

class EConfig;

namespace ds {

enum DS_STATE {
	BURST,
	RUN
};

enum LOG_TYPE {
	DEBUG,
	INFO,
	WARN,
	ERROR
};

/* The bit field values of the enabled tests */
#define TST_ABNORMALS	0x0001
#define TST_JOINCOUNT	0x0002
#define TST_CHANRANGE	0x0004
#define TST_HASOP	0x0008
#define TST_MAXCHANS	0x0010

class dronescan : public xClient {
public:
	/** Constructor receives a configuration file name. */
	dronescan( const string& ) ;
	
	/** Destructor to clean up after ourselves. */
	inline virtual ~dronescan() { } ;
	
	/***********************************************************
	 ** O V E R R I D E N   X C L I E N T   F U N C T I O N S **
	 ***********************************************************/
	 
	/** This method is called when we have attached to the xServer. */
	virtual void ImplementServer( xServer* ) ;
	
	/** This method is called after server connection. */
	virtual int BurstChannels() ;
	
	/** Receive network events. */
	virtual int OnEvent( const eventType&, void*, void*, void*, void* ) ;
	
	/** Receive channel events. */
	virtual int OnChannelEvent( const channelEventType&, Channel*,
		void*, void*, void*, void* ) ;
	
	/** Receive private messages. */
	virtual int OnPrivateMessage( iClient*, const string&, bool ) ;
	
	/** Receive our own timed events. */
	virtual int OnTimer( xServer::timerID , void* ) ;
	
	
	/*****************************************
	 ** D R O N E S C A N   T Y P E D E F S **
	 *****************************************/
	
	typedef unsigned short int testEnabledType;
	
	
	/*******************************************
	 ** D R O N E S C A N   F U N C T I O N S **
	 *******************************************/
	
	/** Change the current state. */
	void changeState(DS_STATE) ;
	
	/** This function handles new clients as they connect. */
	void handleNewClient( iClient* ) ;
	
	/** Calculate global entropy and store it. */
	void calculateEntropy() ;
	
	/** Set states on global nicks. */
	void setNickStates() ;
	
	/** Convenience function to reset states and check channels. */
	inline void resetAndCheck()
		{ setConsoleTopic(); setNickStates(); checkChannels(); }
	
	/**
	 * Check global channels for drones. This is a convenience wrapper
	 * for isAbnormal( Channel* ).
	 */
	void checkChannels() ;
	void checkChannel( const Channel* , const iClient* = 0 ) ;
	
	/** Calculate the entropy of a given string. */
	double calculateEntropy( const string& ) ;
	
	/** Return the entropy of a given client. */
	double calculateEntropy( const iClient* ) ;
	
	/** Check if a channel is normal. */
	/** Check if an iClient's nick is normal. */
	bool isNormal( const iClient* ) ;
	
	/** Set a clientData's state depending on the iClient. */
	CLIENT_STATE setClientState( iClient* );
	
	/** Log a message. */
	void log(LOG_TYPE, char*, ...) ;
	
	/** Set the topic of the console channel. */
	void setConsoleTopic() ;
	
	/** Reply to a given iClient. */
	void Reply(const iClient*, char*, ...) ;
	
	/** See if a given test is enabled. */
	inline bool testEnabled(testEnabledType theTest)
		{ return ((enabledTests & theTest) != 0); }
	
	
	/** Configuration variables used by tests. */
	
	/** Abnormals options */
	double channelMargin;
	
	/** Channel range options */
	double channelRange;
	
	/** Maxchans options */
	unsigned int maxChans;
	 
protected:
	/** Configuration file. */
	EConfig *dronescanConfig;
	
	/** Configuration variables. */
	string consoleChannel;
	string consoleChannelModes;
	
	/** State variable. */
	DS_STATE currentState;
	
	/** Character occurance frequencies. */
	typedef map< char , double > charMapType;
	charMapType charMap;
	
	/** Average nickname entropy. */
	double averageEntropy;
	unsigned int totalNicks;
	
	/** What tests to enable. */
	testEnabledType enabledTests;
	
	/** Margins. */
	double nickMargin;
	unsigned int channelCutoff;
	
	/** Join counter config options */
	unsigned int jcInterval;
	unsigned int jcCutoff;
	typedef map< string , unsigned int , noCaseCompare > jcChanMapType;
	jcChanMapType jcChanMap;
	
	
	/** What level to log to the console. */
	int consoleLevel;
	
	/** Stats. */
	int customDataCounter;
	
	/** Internally used timer. */
	Timer *theTimer;
	
	/** Timers for GNUWorld triggered events. */
	xServer::timerID tidClearJoinCounter;
	
	/** Command map type. */
	typedef map< string , Command* , noCaseCompare > commandMapType;
	typedef commandMapType::value_type commandPairType;
	commandMapType commandMap;
	bool RegisterCommand(Command*);
	
	/** Test map type. */
	typedef vector< Test* > testVectorType;
	testVectorType testVector;
	void RegisterTest(Test*);
}; // class dronescan

} // namespace ds

} // namespace gnuworld

#endif