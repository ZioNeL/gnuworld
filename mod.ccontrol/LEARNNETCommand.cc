/**
 * LEARNNETCommand.cc
 * Causes the bot to automatically update its server db
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 *
 * $Id: LEARNNETCommand.cc,v 1.13 2003/06/28 01:21:19 dan_karrels Exp $
 */

#include	<new>
#include	<string>

#include	<cassert>
#include	<cstdlib>

#include	"ccontrol.h"
#include	"CControlCommands.h"
#include	"StringTokenizer.h"
#include        "iServer.h"
#include	"Network.h"
#include        "server.h"
#include	"ccUser.h"
#include	"misc.h"

const char ccontrol_h_rcsId[] = __CCONTROL_H ;
const char CControlCommands_h_rcsId[] = __CCONTROLCOMMANDS_H ;
const char StringTokenzier_h_rcsId[] = __STRINGTOKENIZER_H ;
const char iServer_h_rcsId[] = __ISERVER_H ;
const char Network_h_rcsId[] = __NETWORK_H ;
const char server_h_rcsId[] = __SERVER_H ;
const char ccUser_h_rcsId[] = __CCUSER_H ;
const char misc_h_rcsId[] = __MISC_H ;
const char LEARNNETCommand_cc_rcsId[] = "$Id: LEARNNETCommand.cc,v 1.13 2003/06/28 01:21:19 dan_karrels Exp $";

namespace gnuworld
{

using std::string ;

namespace uworld
{

bool LEARNNETCommand::Exec( iClient* theClient, const string& Message )
{

if(!dbConnected)
        {
        bot->Notice(theClient,"Sorry, but the db connection is down "
		"now, please try again alittle later");
        return false;
        }

bot->MsgChanLog("LEARNNET \n");

unsigned int AddedServers = 0;
StringTokenizer st(Message);

bot->MsgChanLog("Learning network status at the request of : %s\n",
	theClient->getNickName().c_str());

xNetwork::serverIterator ptr = Network->server_begin();
xNetwork::serverIterator end = Network->server_end();

for( ; ptr != end ; ptr++ )
	{
	iServer* CurServer = ptr->second ;
	if( NULL == CurServer)
		{
		continue ;
		}

	if((!server->isJuped(CurServer)) && 
		(strcmp(CurServer->getName().c_str(),
			bot->getUplinkName().c_str())))
		{
		if(!bot->getServer(CurServer->getName()))
			{
			//If the server isnt in the database , update it
			ccServer* NewServer = new (std::nothrow)
				ccServer(bot->SQLDb);
			assert( NewServer != 0 ) ;

			// TODO: Shouldn't all of this be in the
			// ccServer constructor?
			NewServer->setName(CurServer->getName());
			NewServer->setUplink(Network->findServer(CurServer->getUplinkIntYY())->getName());
			NewServer->setLastNumeric(CurServer->getCharYY());
			NewServer->setLastConnected(CurServer->getConnectTime());
			NewServer->setLastSplitted(0);
			NewServer->setAddedOn(::time(0));
			NewServer->setLastUpdated(::time(0));
			NewServer->setNetServer(CurServer);

			bot->addServer(NewServer);
			bot->Write("%s V :%s\n",
				bot->getCharYYXXX().c_str(),
				CurServer->getCharYY());

			if(NewServer->Insert())
				{
				AddedServers++;
				}	
			else
				{
				bot->MsgChanLog("Error while learning "
					"server : %s\n",
					NewServer->getName().c_str());
				}	
			}
		}
	}

bot->MsgChanLog( "Finished learning the network, Learned a total of %d "
	"servers\n", AddedServers ) ;
bot->Notice( theClient, "Finished learning the network, Learned a "
	"total of %d servers\n", AddedServers ) ;

return true;
}

} // namespace uworld

} // namespace gnuworld

