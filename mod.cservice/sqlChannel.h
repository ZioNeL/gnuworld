/**
 * sqlChannel.h
 * Author: Greg Sikorski
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
 * $Id: sqlChannel.h,v 1.47 2007/08/28 16:10:12 dan_karrels Exp $
 */

#ifndef __SQLCHANNEL_H
#define __SQLCHANNEL_H "$Id: sqlChannel.h,v 1.47 2007/08/28 16:10:12 dan_karrels Exp $"

#include	<string>
#include	<map>
#include	<vector>
#include	<utility>

#include	<ctime>

#include	"dbHandle.h"
#include	"sqlBan.h"

namespace gnuworld
{

using std::string ;
using std::map ;
using std::vector ;

//	< Message < time, count > >
typedef map < string, std::pair < time_t, unsigned int > > floodMessageType;

class chanFloodType
{
private:
	time_t last_time;
	string last_message;
	unsigned int msgCount;
	unsigned int noticeCount;
	unsigned int ctcpCount;
	time_t now;

public:

	unsigned int repCount;

	floodMessageType messageFloodMap;
	floodMessageType noticeFloodMap;
	floodMessageType ctcpFloodMap;

	void setCurrentTime(const time_t&);

	void calcTotalMessageCount(const string&);
	void calcTotalNoticeCount(const string&);
	void calcTotalCTCPCount(const string&);

	inline const time_t& getLastTime()
		{ return last_time; }

	inline void setLastTime(const time_t& _last_time)
		{ last_time = _last_time; }

	inline const string& getLastMessage()
		{ return last_message; }

	inline void setLastMessage(const string& _last_message)
		{ last_message = _last_message; }

	inline const unsigned int& getRepCount()
		{ return repCount; }

	inline void setRepCount(const unsigned int& _repCount)
		{ repCount = _repCount; }

	inline const unsigned int& getTotalMessageCount()
		{ return msgCount; }

	inline void setTotalMessageCount(const unsigned int& _msgCount)
		{ msgCount = _msgCount; }

	inline const unsigned int& getTotalNoticeCount()
		{ return noticeCount; }

	inline void setTotalNoticeCount(const unsigned int& _noticeCount)
		{ noticeCount = _noticeCount; }

	inline const unsigned int& getTotalCTCPCount()
		{ return ctcpCount; }

	inline void setTotalCTCPCount(const unsigned int& _ctcpCount)
		{ ctcpCount = _ctcpCount; }

	chanFloodType();
	virtual ~chanFloodType();
};

class sqlChannel
{

public:
	sqlChannel(dbHandle*) ;
	virtual ~sqlChannel() ;

	typedef unsigned int	flagType ;

	static const flagType	F_NOPURGE;
	static const flagType	F_SPECIAL;
	static const flagType	F_NOREG;
	static const flagType	F_NEVREG;
	static const flagType	F_SUSPEND;
	static const flagType	F_TEMP;
	static const flagType	F_CAUTION;
	static const flagType	F_VACATION;
	static const flagType   F_LOCKED;

	static const flagType	F_ALWAYSOP;
	static const flagType	F_STRICTOP;
	static const flagType	F_NOOP;
	static const flagType	F_AUTOTOPIC;
	static const flagType	F_OPONLY; 	// Deprecated.
	static const flagType	F_AUTOJOIN;
	static const flagType	F_FLOATLIM;
	static const flagType	F_MIA;		// MIA review tag
	static const flagType	F_NOFORCE; // Reserved for use by Planetarion.
	static const flagType	F_NOVOICE;
	static const flagType	F_NOTAKE;
	static const flagType	F_FLOODPRO;
	static const flagType	F_FLOODPROGLINE;

	/*
	 *   Channel 'Event' Flags, used in the channelog table.
	 *   These flags are used to filter channel log records.
	 *   in reports.
	 */

	static const int	EV_MISC;
	static const int	EV_JOIN;
	static const int	EV_PART;
	static const int	EV_OPERJOIN;
	static const int	EV_OPERPART;
	static const int	EV_FORCE;
	static const int	EV_REGISTER;
	static const int	EV_PURGE;

	/* Manually added Comment */
	static const int	EV_COMMENT;
	static const int	EV_REMOVEALL;
	static const int	EV_IDLE;

	/* other events */
	static const int	EV_MGRCHANGE;
	static const int	EV_ADMREJECT;
	static const int	EV_WITHDRAW;
	static const int	EV_NEWAPP;
	static const int	EV_NONSUPPORT;
	static const int	EV_ADMREVIEW;
	static const int	EV_CLRREVIEW;
	static const int	EV_SUSPEND;
	static const int	EV_UNSUSPEND;

	enum FloodType {
		FLOOD_MSG,
		FLOOD_NOTICE,
		FLOOD_CTCP
	};

	enum FloodProLevel {
		FLOODPRO_NONE,
		FLOODPRO_KICK,	//=WARNING
		FLOODPRO_BAN,
		FLOODPRO_GLINE
	};

	/*
	 *  Methods to get data atrributes.
	 */

	inline const unsigned int&	getID() const
		{ return id ; }

	inline const string&		getName() const
		{ return name ; }

	inline const flagType&		getFlags() const
		{ return flags ; }

	inline bool  getFlag( const flagType& whichFlag ) const
		{ return (flags & whichFlag) ; }

	inline const unsigned short int& getMassDeopPro() const
		{ return mass_deop_pro ; }

	inline const unsigned int& getFloodPro() const
		{ return flood_pro ; }

	inline const unsigned short& getFloodMsg() const
		{ return msg_period ; }

	inline const unsigned short int& getFloodNotice() const
		{ return notice_period ; }

	inline const unsigned short int& getFloodCTCP() const
		{ return ctcp_period ; }

	inline const unsigned short int& getFloodPeriod() const
		{ return flood_period ; }

    inline const unsigned short int& getRepeatCount() const
		{ return repeat_count ; }

    inline const FloodProLevel& getFloodproLevel() const
		{ return floodlevel; }

    inline const FloodProLevel& getManualFloodproLevel() const
		{ return man_floodlevel; }

	inline const time_t& 		getLastFloodTime() const
		{ return last_flood; }

	inline const string&		getURL() const
		{ return url ; }

	inline const string&		getDescription() const
		{ return description ; }

	inline const string&		getComment() const
		{ return comment ; }

	inline const string&		getKeywords() const
		{ return keywords ; }

	inline const time_t&		getRegisteredTS() const
		{ return registered_ts ; }

	inline const time_t&		getChannelTS() const
		{ return channel_ts ; }

	inline const string&		getChannelMode() const
		{ return channel_mode ; }

	inline const unsigned short int& getUserFlags() const
		{ return userflags ; }

	inline const time_t&		getLastUpdated() const
		{ return last_updated ; }

	inline const bool& 			getInChan() const
		{ return inChan; }

	inline const time_t&		getLastTopic() const
		{ return last_topic ; }

	inline const time_t&		getLastLimitCheck() const
		{ return last_limit_check ; }

	inline const time_t&		getLastUsed() const
		{ return last_used ; }

	inline const unsigned int& getLimitOffset() const
		{ return limit_offset ; }

	inline const time_t&	getLimitPeriod() const
		{ return limit_period ; }

	inline const unsigned int& getLimitGrace() const
		{ return limit_grace ; }

	inline const unsigned int& getLimitMax() const
		{ return limit_max ; }

	inline const unsigned int& getMaxBans() const
		{ return max_bans ; }

	inline const unsigned int& getNoTake() const
		{ return no_take ; }

	unsigned int getTotalMessageCount(const string& );

	unsigned int getTotalNoticeCount(const string&);

	unsigned int getTotalCTCPCount(const string&);

	/**
	 * Load channel data from the backend using the channel name as
	 * a key.
	 */
	bool loadData( const string& );

	/**
	 * Load channel data from the backend using the channel_id as a
	 * key.
	 */
	bool loadData( int );

	/*
	 *  Methods to set data atrributes.
	 */

	// 'ID' is a primary key and cannot be altered.

	inline void setID( const unsigned int& _id )
		{ id = _id; }

	inline void setName( const string& _name )
		{ name = _name; }

	inline void setFlag( const flagType& whichFlag )
		{ flags |= whichFlag; }

	inline void removeFlag( const flagType& whichFlag )
		{ flags &= ~whichFlag; }

	inline void clearFlags()
		{ flags = 0; }

	inline void setMassDeopPro( const unsigned short int& _mass_deop_pro )
		{ mass_deop_pro = _mass_deop_pro; }

	inline void setFloodPro( const unsigned int& _flood_pro )
		{ flood_pro = _flood_pro; }

	inline void setFloodproLevel( const FloodProLevel& _floodlevel )
		{ floodlevel = _floodlevel; }

	inline void setManualFloodproLevel( const FloodProLevel& _man_floodlevel )
		{ man_floodlevel = _man_floodlevel; }

	inline void incFloodPro()
	{
		if (floodlevel == FLOODPRO_NONE)
			floodlevel = FLOODPRO_KICK;
		else if (floodlevel == FLOODPRO_KICK)
			floodlevel = FLOODPRO_BAN;
#ifdef GLINE_ON_FLOODPRO
		else if ((floodlevel == FLOODPRO_BAN) && (getFlag(sqlChannel::F_FLOODPROGLINE)))
			floodlevel = FLOODPRO_GLINE;
#endif
	}

	inline void decFloodPro()
	{
		if (floodlevel == FLOODPRO_GLINE)
			floodlevel = FLOODPRO_BAN;
		else if (floodlevel == FLOODPRO_BAN)
			floodlevel = FLOODPRO_KICK;
		else if (floodlevel == FLOODPRO_KICK)
			floodlevel = FLOODPRO_NONE;
	}

	inline void setLastFloodTime( const time_t& _last_flood )
		{ last_flood = _last_flood; }

	inline void setURL( const string& _url )
		{ url = _url; }

	inline void setDescription( const string& _description )
		{ description = _description; }

	inline void setComment( const string& _comment )
		{ comment = _comment; }

	inline void setKeywords( const string& _keywords )
		{ keywords = _keywords; }

	inline void setRegisteredTS( const time_t& _registered_ts )
		{ registered_ts = _registered_ts; }

	inline void setChannelTS( const time_t& _channel_ts )
		{ channel_ts = _channel_ts; }

	inline void setChannelMode( const string& _channel_mode )
		{ channel_mode = _channel_mode; }

	inline void setUserFlags( const unsigned short int& _userflags )
		{ userflags = _userflags; }

	inline void setInChan( const bool& _inChan )
		{ inChan = _inChan; }

	inline void setLastTopic( const time_t& _last_topic )
		{ last_topic = _last_topic; }

	inline void setLastLimitCheck( const time_t& _last_limit_check )
		{ last_limit_check = _last_limit_check; }

	inline void setLastUsed( const time_t& _last_used )
		{ last_used = _last_used; }

	inline void setLimitOffset( const unsigned int& _limit_offset )
		{ limit_offset = _limit_offset; }

	inline void setLimitPeriod( const time_t& _limit_period )
		{ limit_period = _limit_period; }

	inline void setLimitGrace( const unsigned int& _limit_grace )
		{ limit_grace = _limit_grace; }

	inline void setLimitMax( const unsigned int& _limit_max )
		{ limit_max = _limit_max; }

	inline void setMaxBans( const unsigned int& _max_bans )
		{ max_bans = _max_bans; }

	inline void setNoTake( const unsigned int& _no_take )
		{ no_take = _no_take; }

	inline void setCurrentTime(const time_t& _now )
		{ now = _now; }

	/**
	 * Method to perform a SQL 'UPDATE' and commit changes to this
	 * object back to the database.
	 */
	bool commit();
	bool insertRecord();
	void setAllMembers(int);

	void setAllFlood();
	void setFloodMsg(const unsigned short& );
	void setFloodNotice(const unsigned short& );
	void setFloodCTCP(const unsigned short& );
	void setFloodPeriod(const unsigned short& );
    void setRepeatCount(const unsigned short& );
    void setDefaultFloodproValues();

    // < total_count, Mask_list >
	typedef std::pair < unsigned int, std::list < string > > repeatMaskMapType;

	static string getFloodLevelName(const FloodProLevel& );
    repeatMaskMapType getRepeatMessageCount(const string&, string Mask = string());
	time_t getMaskLastTime(const string& );
	//void setMaskLastTime(const string&,);
	void RemoveFlooderMask(const string&);
	void handleNewMessage(const FloodType&, const string&, const string&);
	void calcTotalMessageCount(const string&);
	void calcTotalNoticeCount(const string&);
	void calcTotalCTCPCount(const string&);

public:
	/*
	 * Map with key user-id, contents level and username for
	 * easy access
	 * Stores UID's of admin users with forced accessse
	 * on this channel
	 */

	typedef map< unsigned int, std::pair < unsigned short, string > > forceMapType ;
	forceMapType forceMap;

	typedef map < int,sqlBan*> sqlBanMapType;
	sqlBanMapType banList;

	// < repeater_Mask, flooder_struct >
	typedef map < string, chanFloodType* > chanFloodMapType;
	chanFloodMapType chanFloodMap;

protected:

	unsigned int	id ;
	string		name ;
	flagType	flags ;
	unsigned short	mass_deop_pro ;
	unsigned int	flood_pro ;
	unsigned short	msg_period;
	unsigned short	notice_period;
	unsigned short	ctcp_period;
	unsigned short	flood_period;
    unsigned short	repeat_count;
    FloodProLevel		floodlevel;
    FloodProLevel		man_floodlevel; //the variable to keep track which floodpro level was set manually
	string		url ;
	string		description ;
	string		comment ;
	string		keywords  ;
	time_t		registered_ts ;
	time_t		channel_ts ;
	string		channel_mode ;
	unsigned short	userflags ;
	time_t		last_updated ;
	time_t		last_topic ;
	bool		inChan;
	time_t		last_used;
	unsigned int limit_offset;
	time_t limit_period;
	time_t last_limit_check;
	time_t 		last_flood;	//last time when an floodpro measure was taken (kick/ban/gline)
	unsigned int limit_grace;
	unsigned int limit_max;
	unsigned int max_bans;
	unsigned int no_take;
	time_t		now;

	dbHandle*	SQLDb;

 } ;

}

#endif // __SQLCHANNEL_H
