/* 
 * PARTCommand.cc 
 *
 * 10/02/2001 - David Henriksen <david@itwebnet.dk>
 * Initial Version. Written, and finished.
 *
 * Allows an oper to part cmaster from a registered channel.
 *
 * Caveats: None
 *
 * $Id: OPERPARTCommand.cc,v 1.5 2001/02/16 20:20:26 plexus Exp $
 */


#include	<string>
 
#include	"StringTokenizer.h"
#include	"ELog.h" 
#include	"cservice.h"
#include	"levels.h"
#include	"responses.h"
#include	"Network.h"

const char OPERPARTCommand_cc_rcsId[] = "$Id: OPERPARTCommand.cc,v 1.5 2001/02/16 20:20:26 plexus Exp $" ;

namespace gnuworld
{

using namespace gnuworld;
 
bool OPERPARTCommand::Exec( iClient* theClient, const string& Message )
{ 
	/*
	 *  Check if the user is an oper.
	 */

        if(!theClient->isOper())
        {
        	bot->Notice(theClient, "This command is reserved to IRC Operators");
        	return true;
        }

	StringTokenizer st( Message ) ;
	if( st.size() < 2 )
	{
		Usage(theClient);
		return true;
	}

	/* 
	 *  Check the channel is actually registered.
	 */

	sqlUser* theUser = bot->isAuthed(theClient, false);
	sqlChannel* theChan = bot->getChannelRecord(st[1]);
	if (!theChan) {
		bot->Notice(theClient, bot->getResponse(theUser, language::chan_not_reg).c_str(),
			st[1].c_str());
		return false;
	} 

	/* Check the bot is in the channel. */
 
	if (!theChan->getInChan()) {
		bot->Notice(theClient, 
			bot->getResponse(theUser,
				language::i_am_not_on_chan,
				string("I'm not in that channel!")));
		return false;
	}

	bot->writeChannelLog(theChan, theClient, sqlChannel::EV_OPERPART, "");

	// Tell the world. 
 
	strstream s;

	s       << server->getCharYY() << " WA :"
    	        << "An IRC Operator is asking me to leave channel "
        	<< theChan->getName() << ends;
	bot->Write(s);
	delete[] s.str();
	
	bot->logAdminMessage("%s is asking me to leave channel %s",
			theClient->getNickUserHost().c_str(),
			theChan->getName().c_str());
	 
	theChan->setInChan(false);
	bot->getUplink()->UnRegisterChannelEvent(theChan->getName(), bot);
	
	bot->Part(theChan->getName(), "At the request of an IRC Operator");
	
	return true;
} 

} // namespace gnuworld.