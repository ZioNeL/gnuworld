/* gnutest.h */

#ifndef __GNUTEST_H
#define __GNUTEST_H "$Id: gnutest.h,v 1.2 2000/08/04 23:39:09 dan_karrels Exp $"

#include	<string>
#include	<vector>

#include	"client.h"
#include	"iClient.h"

namespace gnuworld
{

using std::string ;
using std::vector ;

class gnutest : public xClient
{

public:
	gnutest( const string& ) ;
	virtual ~gnutest() ;

	virtual int OnChannelEvent( const channelEventType&,
		const string&,
		void* data1 = 0, void* data2 = 0,
		void* data3 = 0, void* data4 = 0 ) ;

	virtual int OnEvent( const eventType& theEvent,
		void* data1 = 0, void* data2 = 0,
		void* data3 = 0, void* data4 = 0 ) ;

	virtual int BurstChannels() ;
	virtual int OnPrivateMessage( iClient*, const string& ) ;

	virtual bool isOnChannel( const string& chanName ) const ;
	virtual bool isOnChannel( const Channel* theChan ) const ;

protected:

	virtual bool	addChan( Channel* ) ;
	virtual bool	removeChan( Channel* ) ;

	string		operChan ;
	vector< string >	channels ;

} ;

} // namespace gnuworld

#endif // __GNUTEST_H
