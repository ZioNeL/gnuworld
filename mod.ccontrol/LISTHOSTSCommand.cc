/**
 * LISTHOSTSCommand.cc
 * Get an oper hosts entry
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
 * $Id: LISTHOSTSCommand.cc,v 1.12 2003/08/09 23:15:33 dan_karrels Exp $
 */

#include	<string>

#include	<cstdlib>

#include	"ccontrol.h"
#include	"CControlCommands.h"
#include	"StringTokenizer.h"
#include	"config.h"

RCSTAG( "$Id: LISTHOSTSCommand.cc,v 1.12 2003/08/09 23:15:33 dan_karrels Exp $" ) ;

namespace gnuworld
{

using std::string ;

namespace uworld
{

bool LISTHOSTSCommand::Exec( iClient* theClient, const string& Message)
{	 
StringTokenizer st( Message ) ;


if(!dbConnected)
        {
        bot->Notice(theClient,"Sorry, but the db connection is down now, please try again alittle later");
        return false;
        }
	
if( st.size() < 2 )
	{
	Usage(theClient);
	return true;
	}
ccUser* tmpUser = bot->IsAuth(theClient);
bot->MsgChanLog("LISTHOSTS %s\n",st.assemble(1).c_str());

tmpUser = bot->GetOper(st[1]);

if(!tmpUser)
	{
        bot->Notice(theClient,"%s isnt on my access list",st[1].c_str());
        return false;
	}

if(bot->listHosts(tmpUser,theClient))
	{
	bot->Notice(theClient,"End of hosts for user %s",st[1].c_str());
	}
else
	{
	bot->Notice(theClient,"Error while accessing %s hostlist",st[1].c_str());
	}

return true;
}

}
} // namespace gnuworld

