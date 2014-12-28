#include "ClockObj.h"

ClockObj::ClockObj()
{
	oldTime = clock();
}


ClockObj::~ClockObj()
{
}

void	ClockObj::restart()
{
	oldTime = clock();
}

float	ClockObj::getElapsedTime() const
{
	clock_t	diff;

	diff = clock() - oldTime;
	return (((float)diff) * 1000.f / CLOCKS_PER_SEC * 1000.f);
}