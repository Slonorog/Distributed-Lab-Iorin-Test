#include "Time.h"
#include <string>

Time::Time( unsigned short _h, unsigned short _m, unsigned short _s):
	Hour(_h),Minute(_m),Second(_s)
{
	if (_h > 24 || _m > 60 || _s > 60)
		throw std::exception("Incorrect time");
}

Time::Time(const Time & _t)
	:Hour(_t.Hour),Minute(_t.Minute), Second(_t.Second)
{

}

Time::Time( char * source)
{
	temp = source;
	//strcpy(temp, source);
}

void Time::Init()
{
	temp = strtok(temp, ":");
	Hour = atoi(temp);
	temp = strtok(0, ":");
	Minute = atoi(temp);
	temp = strtok(0, ":");
	Second = atoi(temp);
}
