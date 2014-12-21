#pragma once

#include <string>
#include <iostream>
#include <process.h>
#include <stdio.h>

#include "IThread.h"

class LinThread : public IThread
{
protected:
	int		_port;

public:
	LinThread(int port);
	virtual ~LinThread();

	virtual void	start();
	virtual bool	run();
	static void		call_run(void *ptr);
};

