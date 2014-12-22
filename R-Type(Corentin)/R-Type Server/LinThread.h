#pragma once

#include <string>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "IThread.h"

class LinThread : public IThread
{
protected:
	int				_port;
	IUDPServSocket	*_socket;
public:
	LinThread(int port);
	virtual ~LinThread();

	virtual bool	start();
	virtual bool	run();
	static void	*call_run(void *ptr);
};

