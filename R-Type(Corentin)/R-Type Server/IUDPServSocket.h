#pragma once
#include <iostream>
#include <string>

class IUDPServSocket
{
public :
	virtual ~IUDPServSocket() {}

	virtual bool	Connect(int port) = 0;
	virtual bool	Receive_data() = 0;
protected:
	virtual bool	send_data(struct sockaddr_in *target) = 0;
};