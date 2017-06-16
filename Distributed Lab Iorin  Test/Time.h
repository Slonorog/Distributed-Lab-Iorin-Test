
#pragma once
#include <exception>
struct Time
{
	Time(unsigned short _h, unsigned short _m, unsigned short _s);
	Time(const Time &_t);
	Time(char* str);
	short Hour;
	short Minute;
	short Second;
	void Init();
private:
	char* temp;
	
	
};

