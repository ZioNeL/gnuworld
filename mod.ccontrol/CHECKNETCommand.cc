/**
 * CHECKNETCommand.cc
 * Check the network stauts
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
 * $Id: CHECKNETCommand.cc,v 1.14 2004/03/25 20:55:40 mrbean_ Exp $
 */

#include	<string>
#include	<cstdlib>
#include        <iomanip>
#include	"ccontrol.h"
#include	"CControlCommands.h"
#include	"StringTokenizer.h"
#include	"ccServer.h"
#include	"config.h"

RCSTAG( "$Id: CHECKNETCommand.cc,v 1.14 2004/03/25 20:55:40 mrbean_ Exp $" ) ;

namespace gnuworld
{

using std::string ;

namespace uworld
{

bool CHECKNETCommand::Exec( iClient* theClient, const string& )
{
unsigned int TServers = 0;

bot->Notice(theClient,"Checking network status as for %d\n",::time(NULL));
bot->MsgChanLog("CHECKNET\n");
ccServer* CurServer;
string Msg;
char tNum[512];		    
for (ccontrol::serversConstIterator ptr = bot->serversMap_begin() ; 
	ptr != bot->serversMap_end();++ptr)
	{ //For each server on the database check if its connetcted
	CurServer = ptr->second;
	if(CurServer->getReportMissing() && !CurServer->getNetServer()) //If the server isnt connected 
		{
		Msg = "Server \002";
		Msg += CurServer->getName(); 
		Msg +="\002 Is missing, ";
		Msg += "Last split time : ";
		if(CurServer->getLastSplitted() != 0)
			{
			sprintf(tNum,"%li",CurServer->getLastSplitted());
			Msg += tNum;
			Msg += " Split Reason:";
			Msg += CurServer->getSplitReason();
			}
		else
			Msg += " unknown ";
			
		Msg += " Last connection time : ";
		
		if(CurServer->getLastConnected() != 0)
			{
			sprintf(tNum,"%li",CurServer->getLastConnected());
			Msg += tNum;
			}
		else
			Msg += " unknown ";
		bot->Notice(theClient,"%s",Msg.c_str());
		TServers++;
		}
	}


bot->Notice(theClient,"Finished checking the network status\n");
bot->Notice(theClient,"Found a total of %d missing servers\n",TServers);
return true;

}

}
}
