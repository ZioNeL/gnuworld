/**
 * OPCommand.cc
 * Cause the bot to op users on a specific channel
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
 * $Id: OPCommand.cc,v 1.11 2003/08/09 23:15:33 dan_karrels Exp $
 */

#include	<string>

#include	<cstdlib>

#include	"ccontrol.h"
#include	"CControlCommands.h"
#include	"StringTokenizer.h"
#include	"Network.h"
#include	"Constants.h"
#include	"ccBadChannel.h"
#include	"config.h"

RCSTAG( "$Id: OPCommand.cc,v 1.11 2003/08/09 23:15:33 dan_karrels Exp $" ) ;

namespace gnuworld
{

using std::string ;

namespace uworld
{

bool OPCommand::Exec( iClient* theClient, const string& Message )
{

StringTokenizer st( Message ) ;
if( st.size() < 3 )
	{
	Usage( theClient ) ;
	return true ;
	}

if(st[1].size() > channel::MaxName)
	{
	bot->Notice(theClient,"Channel name can't be more than %d chars",channel::MaxName);
	return false;
	}
Channel* theChan = Network->findChannel( st[ 1 ] ) ;
if( NULL == theChan )
	{
	bot->Notice( theClient, "Unable to find channel %s\n",
		st[ 1 ].c_str() ) ;
	return true ;
	}
ccBadChannel* Chan = bot->isBadChannel(st[1]);
if(Chan)
	{
	bot->Notice(theClient,"Sorry, but you can not change modes in "
			     "this channel because : %s"
			     ,Chan->getReason().c_str());
	return false;
	}
	
iClient* Target = 0;

typedef map < iClient*, int > duplicateMapType; 
duplicateMapType duplicateMap; 


string mode = "+";
string args = "";
bot->MsgChanLog("OP %s\n",st.assemble(1).c_str());

for(unsigned int i=2;i<st.size();i++)
	{
	Target = Network->findNick( st[ i ] ) ;
	if(Target)
		{
		ChannelUser* tmpChanUser = theChan->findUser(Target) ;

		//Check if the user is in the channel and op him, even if he's opped
		if( tmpChanUser )
			{
			duplicateMapType::iterator ptr = duplicateMap.find(Target);
			if(ptr == duplicateMap.end())
				{ 
				// Not a duplicate.
				duplicateMap.insert(duplicateMapType::value_type(Target, 0)); 
				tmpChanUser->setMode(ChannelUser::MODE_O);
				mode+='o';
				args += Target->getCharYYXXX() + ' ' ;
				}
			} //if
		} //if
	} // for
if(!args.empty())
	bot->ModeAsServer( theChan, mode + ' ' + args ) ;
return true;
}

}
} // namespace gnuworld

