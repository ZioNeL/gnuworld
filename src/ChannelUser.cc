/**
 * ChannelUser.cc
 * Copyright (C) 2002 Daniel Karrels <dan@karrels.com>
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
 * $Id: ChannelUser.cc,v 1.7 2003/08/09 23:15:36 dan_karrels Exp $
 */

#include	<string>

#include	<cassert>

#include	"iClient.h"
#include	"ChannelUser.h"

RCSTAG("$Id: ChannelUser.cc,v 1.7 2003/08/09 23:15:36 dan_karrels Exp $" ) ;

namespace gnuworld
{

using std::string ;

const ChannelUser::modeType ChannelUser::MODE_O = 0x01 ;
const ChannelUser::modeType ChannelUser::MODE_V = 0x02 ;
const ChannelUser::modeType ChannelUser::ZOMBIE = 0x04 ;

ChannelUser::ChannelUser( iClient* _theClient )
 : theClient( _theClient ),
   modes( 0 )
{
assert( theClient != 0 ) ;
}

ChannelUser::~ChannelUser()
{}

const string& ChannelUser::getNickName() const
{
return theClient->getNickName() ;
}

const string& ChannelUser::getUserName() const
{
return theClient->getUserName() ;
}

const string& ChannelUser::getHostName() const
{
return theClient->getInsecureHost() ;
}

const unsigned int& ChannelUser::getIP() const
{
return theClient->getIP() ;
}

const string ChannelUser::getCharYYXXX() const
{
return theClient->getCharYYXXX() ;
}

const unsigned int ChannelUser::getIntYY() const
{
return theClient->getIntYY() ;
}

const unsigned int ChannelUser::getIntXXX() const
{
return theClient->getIntXXX() ;
}

const unsigned int ChannelUser::getIntYYXXX() const
{
return theClient->getIntYYXXX() ;
}

bool ChannelUser::isOper() const
{
return theClient->isOper() ;
}

} //  namespace gnuworld
