/**
 * RANGETest.cc
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
 * $Id: RANGETest.cc,v 1.6 2003/12/29 23:59:37 dan_karrels Exp $
 *
 * Checks the range of the entropy of a given channel.
 */

#include	<sstream>

#include "config.h"
#include "dronescan.h"
#include "dronescanTests.h"

RCSTAG("$Id: RANGETest.cc,v 1.6 2003/12/29 23:59:37 dan_karrels Exp $");

namespace gnuworld {

namespace ds {

bool RANGETest::isNormal( const Channel *theChannel )
{
	double maxEntropy, minEntropy;
	maxEntropy = minEntropy = 0;
	
	bool hasOp = false;
	
	Channel::const_userIterator chanItr = theChannel->userList_begin();
	
	for( ; chanItr != theChannel->userList_end() ; ++chanItr )
		{
		iClient *targetClient = chanItr->second->getClient();
		
		double userEntropy = bot->calculateEntropy(targetClient);
		
		if(userEntropy < minEntropy || minEntropy == 0) minEntropy = userEntropy;
		if(userEntropy > maxEntropy) maxEntropy = userEntropy;
		
		if(chanItr->second->isModeO()) hasOp = true;
		}
	
	if((maxEntropy - minEntropy) > channelRange)
		return true;
	else
		return false;
}


bool RANGETest::setVariable( const string& var, const string& value )
{
	if("CHANNELRANGE" != var) return false;
	
	channelRange = atoi(value.c_str());
	
	return true;
}


const string RANGETest::getVariable() const
{
	return "channelRange";
}


const string RANGETest::getStatus() const
{
	std::stringstream status;
	status << "channelRange: " << channelRange;
	return status.str();
}

} // namespace ds

} // namespace gnuworld
