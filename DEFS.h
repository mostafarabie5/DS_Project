#ifndef _DEFS_
#define _DEFS_
#include<ostream>

struct Pair
{
	int First;
	int Second;

	friend ostream& operator <<(ostream& out, Pair p)
	{
		out << p.First << " " << p.Second;
		return out;
	}
};


#endif