#pragma once
#include <iostream>
#include <string>

class IThread
{
public:
	virtual ~IThread() {}

	virtual void	start() = 0;
	virtual bool	run() = 0;
};