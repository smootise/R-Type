#pragma once
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <algorithm>

#include "ITCPServSocket.h"
#include "Selector.h"
#include "CircularBuff.h"

class TCPWinServSocket :	public ITCPServSocket
{
protected:
	SOCKET					_fathersocket;
	std::vector<Client>		&_clients;

public:
	TCPWinServSocket(std::vector<Client> &client);
	virtual ~TCPWinServSocket(void);

	virtual bool	Connect(int port, Selector &sel);
	virtual bool	SearchNewClients(Selector &sel);
	virtual void	ReadData(CircularBuff &buff, Selector &sel);
	virtual void	SendData(CircularBuff &buff, Selector &sel);
};

