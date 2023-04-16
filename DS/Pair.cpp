#include "Pair.h"
using namespace std;
Pair::Pair()
{
	first = second = 0;
}

void Pair::setFirst(int n)
{
	first = n;
}

void Pair::setSecond(int n)
{
	second = n;
}

int Pair::getFirst()
{
	return first;
}

int Pair::getSecond()
{
	return second;
}

void Pair::operator=(const Pair& p)
{
	first = p.first;
	second = p.second;
}



