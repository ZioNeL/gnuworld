/**
 * msg_EA.cc
 */

#include	<cstring>

#include	"server.h"
#include	"Network.h"
#include	"events.h"
#include	"ELog.h"
#include	"iServer.h"

const char msg_EA_cc_rcsId[] = "$Id: msg_EA.cc,v 1.1 2001/02/02 18:10:30 dan_karrels Exp $" ;

using std::string ;
using std::vector ;
using std::list ;
using std::endl ;
using std::ends ;
using std::strstream ;
using std::stack ;
using std::unary_function ;

namespace gnuworld
{

// Q EA
// Q: Remote server numeric
// EA: End Of Burst Acknowledge
// Our uplink server has acknowledged our EB
int xServer::MSG_EA( xParameters& Param )
{
if( !strcmp( Param[ 0 ], Uplink->getCharYY() ) )
	{
	// My uplink! :)
	// Reset EOB just to be sure
	bursting = false ; // ACKNOWLEDGE! :)
	}

if( !bursting )
	{
	iServer* theServer = Network->findServer( Param[ 0 ] ) ;
	if( NULL == theServer )
		{
		elog	<< "xServer::MSG_EA> Unable to find server: "
			<< Param[ 0 ] << endl ;
		return -1 ;
		}

	PostEvent( EVT_BURST_ACK, static_cast< void* >( theServer ) );
	}
return( 0 ) ;

}

} // namespace gnuworld
