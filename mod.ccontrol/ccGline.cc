/* 
 * ccGline.cc
 * 
 * Gline class
 * 
 * $Id: ccGline.cc,v 1.4 2001/05/14 21:26:37 mrbean_ Exp $
 */
 
#include	<strstream>
#include	<string> 

#include	<ctime>
#include	<cstring> 
#include	<cstdlib>

#include	"libpq++.h"
#include	"ELog.h"
#include	"misc.h"
#include	"ccGline.h" 

const char ccGline_h_rcsId[] = __CCGLINE_H ;
const char ccGline_cc_rcsId[] = "$Id: ccGline.cc,v 1.4 2001/05/14 21:26:37 mrbean_ Exp $" ;

namespace gnuworld
{

using std::string ; 
using std::endl ; 
using std::strstream ;
using std::ends ;

ccGline::ccGline(PgDatabase* _SQLDb)
 : Id(),
   AddedBy(),
   AddedOn( 0 ),
   Expires( 0 ),
   Reason(),
   SQLDb( _SQLDb )
{
}

ccGline::~ccGline()
{}

bool ccGline::Insert()
{
static const char *Main = "INSERT into Glines (Host,AddedBy,AddedOn,ExpiresAt,Reason) VALUES ('";

strstream theQuery;
theQuery	<< Main
		<< Host << "','"
		<< AddedBy << "',"
		<< AddedOn << ","
		<< Expires << ",'"
		<< Reason << "')"
		<< ends;

elog	<< "Gline::Insert::sqlQuery> "
	<< theQuery.str()
	<< endl; 

ExecStatusType status = SQLDb->Exec( theQuery.str() ) ;
delete[] theQuery.str() ;

if( PGRES_COMMAND_OK == status ) 
	{
	return true;
	}
else
	{
	elog	<< "ccontrol::Gline::Insert> SQL Failure: "
		<< SQLDb->ErrorMessage()
		<< endl ;
	return false;
	}

}

bool ccGline::Update()
{
static const char *Main = "UPDATE Glines SET Id = '";

strstream theQuery;
theQuery	<< Main
		<< Id
		<< "', Host = '"
		<< Host
		<< "', AddedBy = '"
		<< AddedBy
		<< "', AddedOn = "
		<< AddedOn
		<< ",ExpiresAt = "
		<< Expires
		<<  ",Reason = '"
		<< Reason << "'"
		<< " WHERE Id = " << Id
		<<  ends;

elog	<< "ccontrol::Gline::Update> "
	<< theQuery.str()
	<< endl; 

ExecStatusType status = SQLDb->Exec( theQuery.str() ) ;
delete[] theQuery.str() ;

if( PGRES_COMMAND_OK == status ) 
	{
	return true;
	}
else
	{
	elog	<< "ccontrol::Gline::Update> SQL Failure: "
		<< SQLDb->ErrorMessage()
		<< endl ;
	return false;
	}
}

bool ccGline::loadData(int GlineId)
{
static const char *Main = "SELECT * FROM glines WHERE Id = ";

strstream theQuery;
theQuery	<< Main
		<< GlineId
		<< ends;

elog	<< "ccontrol::glineConstructor> "
	<< theQuery.str()
	<< endl; 

ExecStatusType status = SQLDb->Exec( theQuery.str() ) ;
delete[] theQuery.str() ;

if( PGRES_TUPLES_OK != status )
	{
	elog	<< "ccGline::ccGline> SQL Failure: "
		<< SQLDb->ErrorMessage()
		<< endl ;

	return false ;
	}


Id = SQLDb->GetValue(0,0);
Host = SQLDb->GetValue(0,1);
AddedBy = SQLDb->GetValue(0,2) ;
AddedOn = static_cast< time_t >( atoi( SQLDb->GetValue(0,3) ) ) ;
Expires = static_cast< time_t >( atoi( SQLDb->GetValue(0,4) ) ) ;
Reason = SQLDb->GetValue(0,5);

return true;
}
bool ccGline::loadData( string & Host)
{
static const char *Main = "SELECT * FROM glines WHERE Host = ";

strstream theQuery;
theQuery	<< Main
		<< Host.c_str()
		<< ends;

elog	<< "ccontrol::glineConstructor> "
	<< theQuery.str()
	<< endl; 

ExecStatusType status = SQLDb->Exec( theQuery.str() ) ;
delete[] theQuery.str() ;

if( PGRES_TUPLES_OK != status )
	{
	elog	<< "ccGline::ccGline> SQL Failure: "
		<< SQLDb->ErrorMessage()
		<< endl ;

	return false ;
	}


Id = SQLDb->GetValue(0,0);
Host = SQLDb->GetValue(0,1);
AddedBy = SQLDb->GetValue(0,2) ;
AddedOn = static_cast< time_t >( atoi( SQLDb->GetValue(0,3) ) ) ;
Expires = static_cast< time_t >( atoi( SQLDb->GetValue(0,4) ) ) ;
Reason = SQLDb->GetValue(0,5);

return true;
}

} //Namespace Gnuworld
