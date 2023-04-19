#pragma once
#include<ostream>
class Pair
{
	int first;
	int second;

public:
	Pair();
	void setFirst(int);
	void setSecond(int);
	int getFirst();
	int getSecond();
	void operator=(const Pair& p);
	void Print();

};

