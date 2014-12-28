#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/uio.h>
#include <unistd.h>
#include <cstdlib>
#include <string.h> //requis pour memset
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>

#include "ITCPSocket.h"

# define	INVALID_SOCKET	-1 

class TCPLinSocket : public ITCPSocket
{
protected:
	int				_fathersocket;

public:
	TCPLinSocket(void);
	virtual ~TCPLinSocket(void);

	virtual bool	ConnectToServer(std::string &hostname, std::string port, Selector &sel);
	virtual bool	ReadData(CircularBuff &buff, Selector &sel);
	virtual void	SendData(CircularBuff &buff, Selector &sel);
};

