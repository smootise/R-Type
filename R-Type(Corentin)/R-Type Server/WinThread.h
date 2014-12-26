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
	ClientMessage	*_recv_msg;
	ServerMessage	*_send_msg;
	Spawner			_spawner;

public:
	WinThread(int port);
	virtual ~WinThread();

	virtual bool	start();
	virtual bool	run();
protected:
	virtual void	analyse_data();

public:
	static void		call_run(void *ptr);
};

