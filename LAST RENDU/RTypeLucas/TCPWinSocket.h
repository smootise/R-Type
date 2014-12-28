#pragma once
#include "ITCPSocket.h"


class TCPWinSocket : public ITCPSocket
{
protected:
	SOCKET				_fathersocket;

public:
	TCPWinSocket(void);
	virtual ~TCPWinSocket(void);

	virtual bool	ConnectToServer(std::string &hostname, std::string port, Selector &sel);
	virtual bool	ReadData(CircularBuff &buff, Selector &sel);
	virtual void	SendData(CircularBuff &buff, Selector &sel);
};

