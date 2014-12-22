#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>

#include "IUDPSocket.h"

class UDPWinSocket : public IUDPSocket
{
protected:
	struct sockaddr_in		_server;
	struct sockaddr_in		_client;
	SOCKET					_socket;
	std::string				_ipsource;
	bool					_connected;

public:
	UDPWinSocket(std::string &ipsource);
	virtual ~UDPWinSocket();

	virtual bool	Connect(int port);
	virtual bool	Send_data();
	virtual bool	Receive_data();
	virtual bool	is_connected();
};

