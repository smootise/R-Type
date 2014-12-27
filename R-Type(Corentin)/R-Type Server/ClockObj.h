#pragma once

#include <ctime>

class ClockObj
{
	clock_t	oldTime;
public:
	ClockObj();
	~ClockObj();
	void	restart();
	float	getElapsedTime() const;
};

