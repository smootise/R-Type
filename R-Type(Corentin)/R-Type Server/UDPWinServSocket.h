#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#include "IUDPServSocket.h"

class UDPWinServSocket :  public IUDPServSocket
{
protected:
	struct sockaddr_in		_serv;
	SOCKET					_socket;

public:
	UDPWinServSocket();
	virtual ~UDPWinServSocket();

	virtual bool	Connect(int port);
	virtual bool	Receive_data();
protected:
	virtual bool	send_data(struct sockaddr_in *target);
};

