/* misc.h
 * Author: Daniel Karrels (dan@karrels.com
 * $Id: misc.h,v 1.19 2002/05/23 20:35:42 dan_karrels Exp $
 * Purpose: This file contains a few miscellaneous methods.
 */

#ifndef __MISC_H
#define __MISC_H "$Id: misc.h,v 1.19 2002/05/23 20:35:42 dan_karrels Exp $"

#include	<string>

#include	<cctype>
#include	<cstring>

#include	"match.h"
#include	"defs.h"

#ifdef GNU_EXTENSIONS
 #include       <ext/hash_map>
#else
 #include       <hash_map>
#endif

namespace gnuworld
{

using HASHMAPNS::hash ;
using HASHMAPNS::hash_map ;
using std::string ;

/**
 * Return 0 if the two strings are equivalent, according to
 * case insensitive searches.
 * Otherwise, it returns the comparison between
 * s1 and s2.
 */
int strcasecmp( const string&, const string& ) ;

/**
 * Case insensitive comparison struct for use by STL structures/algorithms.
 */
struct noCaseCompare
{
inline bool operator()( const string& lhs, const string& rhs ) const
	{
	return (strcasecmp( lhs, rhs ) < 0) ;
	}
} ;

/**
 * A case insensitive binary predicate comparator for two
 * std::string's.
 */
struct eqstr
{
inline bool operator()( const string& s1, const string& s2 ) const
	{
	return (0 == strcasecmp( s1, s2 )) ;
	}
} ;

/**
 * A hashing operator for the system hash tables.
 */
struct eHash
{
inline size_t operator()( const string& s ) const
	{
	if( s.empty() )
		{
		return 0 ;
		}

	register size_t __h = 0 ;
	for ( register const char* ptr = s.c_str() ; *ptr ; ++ptr )
		{
		__h = (5 * __h) + tolower( *ptr ) ;
		}
	return __h ;
	}
} ;

/**
 * A functor suitable for using in STL style containers which provides
 * wildcard matching routine.
 */
struct Match
{
inline bool operator()( const string& lhs, const string& rhs ) const
	{
	return (match( lhs, rhs ) < 0) ;
	}
} ;

/**
 * Return a copy of a given C++ string, whose characters
 * are all lower case.
 */
string string_lower( const string& ) ;

/**
 * Return a copy of a given C++ string, whose
 * characters are all upper case.
 */
string string_upper( const string& ) ;

/**
 * Convert all characters of a given C++ string to
 * lower case.
 */
void string_tolower( string& ) ;

/**
 * Convert all characters of a given C++ string to
 * upper case.
 */
void string_toupper( string& ) ;

/**
 * Examine a given C++ string and return true if it contains
 * all numeric characters, return false otherwise.
 */
bool IsNumeric( const string& ) ;

/**
 * Count the number of occurences of the given character in the
 * given string.
 */
size_t countChar( const string&, const char& ) ;


} // namespace gnuworld

#endif /* __MISC__ */
