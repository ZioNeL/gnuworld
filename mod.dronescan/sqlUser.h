#ifndef SQLUSER_H
#define SQLUSER_H "$Id: sqlUser.h,v 1.2 2003/08/02 18:17:21 jeekay Exp $"

#include <string>

class PgDatabase;

namespace gnuworld {

namespace ds {

using std::string;

class sqlUser {
public:
	sqlUser(PgDatabase*);
	virtual ~sqlUser();
	
	typedef unsigned int flagType;
	static const flagType F_SUSPENDED;
	
	/* Accessors */
	
	inline const string& getUserName() const
		{ return user_name; }
	
	inline const int getCreated() const
		{ return created; }
	
	inline const unsigned int getLastSeen() const
		{ return last_seen; }
	
	inline const string& getLastUpdatedBy() const
		{ return last_updated_by; }
	
	inline const unsigned int getLastUpdated() const
		{ return last_updated; }
	
	inline const unsigned int getAccess() const
		{ return access; }
	
	/* Mutators */
	
	inline void setUserName(const string& _user_name)
		{ user_name = _user_name; }
	
	inline void setCreated(const unsigned int _created)
		{ created = _created; }
	
	inline void setLastSeen(const unsigned int _last_seen)
		{ last_seen = _last_seen; }
	
	inline void setLastUpdatedBy(const string& _last_updated_by)
		{ last_updated_by = _last_updated_by; }
	
	inline void setLastUpdated(const unsigned int _last_updated)
		{ last_updated = _last_updated; }
	
	inline void setAccess(const unsigned int _access)
		{ access = _access; }
	
	inline void setFlags(const flagType _flags)
		{ flags = _flags; }
	
	/* Convenience functions for flags */
	inline const bool isSuspended() const
		{ return (flags & F_SUSPENDED); }
	
	
	/* Methods to alter our SQL status */
	void setAllMembers(int);
	bool commit();
	bool insert();
	bool remove();

protected:
	string		user_name;
	unsigned int	created;
	unsigned int	last_seen;
	string		last_updated_by;
	unsigned int	last_updated;
	unsigned int	flags;
	unsigned int	access;
	
	PgDatabase*	SQLDb;
}; // class sqlUser

} // namespace ds

} // namespace gnuworld

#endif