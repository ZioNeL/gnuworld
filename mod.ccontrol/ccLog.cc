
/*

 */
 
#include "ccLog.h"
#include <fstream>
#include "ELog.h"
#include <string>
#include "StringTokenizer.h"

using namespace std;

namespace gnuworld
{

namespace uworld
{

bool ccLog::Save(fstream& out)
{

if(out.bad())
	{
	return false;
	}


out 	<< Time
        << " " << User.c_str()
	<< " " << Host.c_str()
	<< " " << Desc.c_str()
	<< "\n";
return true;

}

bool ccLog::Load(fstream& in)
{

if((in.bad()) || (in.eof()))
	{
	return false;
	}
char read[513];
if(!in.getline(read,512))
	{
	return false;
	}
StringTokenizer st(read);
if(st.size() < 4)
	{
	elog << "invalid number of args in logs!" << endl;
	return false;
	}
Time = atoi(st[0].c_str());
User = st[1];
Host = st[2];
CommandName = st[3];
Desc = st.assemble(3);

return true;

}


}
}