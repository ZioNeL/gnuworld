/**
 * msg_PASS.cc
 */

#include	"server.h"
#include	"xparameters.h"

const char msg_PASS_cc_rcsId[] = "$Id: msg_PASS.cc,v 1.1 2001/02/02 18:10:30 dan_karrels Exp $" ;

namespace gnuworld
{

int xServer::MSG_PASS( xParameters& )
{
bursting = true ;
return 0 ;
}


} // namespace gnuworld
