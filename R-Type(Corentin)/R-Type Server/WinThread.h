#pragma once

#include <string>
#include <iostream>
#include <process.h>
#include <stdio.h>

#include "IThread.h"

class WinThread : public IThread
{
protected:
	int				_port;
	IUDPServSocket	*_socket;
public:
	WinThread(int port);
	virtual ~WinThread();

	virtual bool	start();
	virtual bool	run();
	static void		call_run(void *ptr);
};

