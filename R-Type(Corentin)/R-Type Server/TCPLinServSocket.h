#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <vector>
#include <algorithm>

#include "ITCPServSocket.h"
#include "Selector.h"
#include "CircularBuff.h"
#include "Client.h"

# define	INVALID_SOCKET	-1 

class TCPLinServSocket : public ITCPServSocket
{
protected:
	SOCKET			_fathersocket;
	std::vector<Client>	&_clients;

public:
	TCPLinServSocket(std::vector<Client> &client);
	virtual ~TCPLinServSocket(void);

	virtual bool	Connect(int port, Selector &sel);
	virtual bool	SearchNewClients(Selector &sel);
	virtual void	ReadData(CircularBuff &buff, Selector &sel);
	virtual void	SendData(CircularBuff &buff, Selector &sel);
};

