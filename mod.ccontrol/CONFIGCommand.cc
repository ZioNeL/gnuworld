/**
 * CONFIGCommand.cc 
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
 * $Id: CONFIGCommand.cc,v 1.8 2005/01/08 23:33:42 dan_karrels Exp $
 */

#include	<string>

#include	"StringTokenizer.h"
#include	"ccontrol.h"
#include	"CControlCommands.h"
#include	"config.h"

RCSTAG( "$Id: CONFIGCommand.cc,v 1.8 2005/01/08 23:33:42 dan_karrels Exp $" ) ;

namespace gnuworld
{

using std::string ;
using std::endl ;
using std::ends ;

namespace uworld
{

bool CONFIGCommand::Exec( iClient* theClient, const string& Message)
{
StringTokenizer st(Message);

if(st.size() < 3)
	{
	Usage(theClient);
	return true;
	}

bot->MsgChanLog("CONFIG %s",st.assemble(1).c_str());
	
for(unsigned int  pos =1; pos < st.size() ;)
	{
	if(!strcasecmp(st[pos],"-VClones"))
		{
		if(st.size() < pos +2)
			{
			bot->Notice(theClient,"-VClones must get the number of virtual clones");
			return true;
			}
		if(!bot->updateMisc("VClones",atoi(st[pos+1].c_str())))
			{
			bot->MsgChanLog("Error while updating the max virtual clones in the db!\n");
			}
		else
			{
			bot->Notice(theClient,"%s was successfully updated to %s",
				    st[pos].c_str(),st[pos+1].c_str());
			}
		pos+=2;
		}
	else if(!strcasecmp(st[pos],"-Clones"))
		{
		if(st.size() < pos +2)
			{
			bot->Notice(theClient,"-Clones must get the number of virtual clones");
			return true;
			}
		if(!bot->updateMisc("Clones",atoi(st[pos+1].c_str())))
			{
			bot->MsgChanLog("Error while updating the max clones in the db!\n");
			}
		else
			{
			bot->Notice(theClient,"%s was successfully updated to %s",
				    st[pos].c_str(),st[pos+1].c_str());
			}
		pos+=2;			
		}
	else if(!strcasecmp(st[pos],"-GBCount"))
		{
		if(st.size() < pos +2)
			{
			bot->Notice(theClient,"-GBCount must get the number glines to burst");
			return true;
			}
		if(!bot->updateMisc("GlineBurstCount",atoi(st[pos+1].c_str())))
			{
			bot->MsgChanLog("Error while updating the gline burst count in the db!\n");
			}
		else
			{
			bot->Notice(theClient,"%s was successfully updated to %s",
				    st[pos].c_str(),st[pos+1].c_str());
			}
		pos+=2;			
		}
	else if(!strcasecmp(st[pos],"-GBInterval"))
		{
		if(st.size() < pos +2)
			{
			bot->Notice(theClient,"-GBInterval must get the number of seconds between each burst");
			return true;
			}
		if(!bot->updateMisc("GlineBurstInterval",atoi(st[pos+1].c_str())))
			{
			bot->MsgChanLog("Error while updating the gline burst interval in the db!\n");
			}
		else
			{
			bot->Notice(theClient,"%s was successfully updated to %s",
				    st[pos].c_str(),st[pos+1].c_str());
			}
		pos+=2;			
		}
	else if(!strcasecmp(st[pos],"-GTime"))
		{
		if(st.size() < pos +2)
			{
			bot->Notice(theClient,"-GTime must get the duration in seconds for the excessive connections gline");
			return true;
			}
		if(!bot->updateMisc("GTime",atoi(st[pos+1].c_str())))
			{
			bot->MsgChanLog("Error while updating the gline duration in the db!\n");
			}
		else
			{
			bot->Notice(theClient,"%s was successfully updated to %s",
				    st[pos].c_str(),st[pos+1].c_str());
			}

		pos+=2;			
		}

	else if(!strcasecmp(st[pos],"-SGline"))
		{
		if(st.size() < pos +2)
			{
			bot->Notice(theClient,"-SGline must get a yes/no answer indicating whether or not to save glines");
			return true;
			}
		if(!bot->updateMisc("SGLine",(strcasecmp(st[pos+1],"YES") == 0) ? 1 : 0))
			{
			bot->MsgChanLog("Error while updating the save gline flag in the db\n");
			}
		else
			{
			bot->Notice(theClient,"%s was successfully updated to %s",
				    st[pos].c_str(),st[pos+1].c_str());
			}
		pos+=2;			
		}

	else
		{
		bot->Notice(theClient,"Sorry, i am not familiar with option %s",st[pos].c_str());
		++pos;
		}
	}	
return true ;
}

}

} // namespace gnuworld
