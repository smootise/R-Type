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
	ClientMessage	*_recv_msg;
	ServerMessage	*_send_msg;

public:
	LinThread(int port);
	virtual ~LinThread();

	virtual bool	start();
	virtual bool	run();

protected:
	virtual void	analyse_data();
public:
	static void	*call_run(void *ptr);
};

