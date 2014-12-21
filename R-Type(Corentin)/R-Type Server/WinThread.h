#pragma once

#include <string>
#include <iostream>
#include <process.h>
#include <stdio.h>

#include "IThread.h"

class WinThread : public IThread
{
protected:
	int		_port;

public:
	WinThread(int port);
	virtual ~WinThread();

	virtual void	start();
	virtual bool	run();
	static void		call_run(void *ptr);
};

