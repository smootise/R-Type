#pragma once

#include <string>
#include <iostream>

class IUDPSocket
{
public:
	virtual ~IUDPSocket() {}

	virtual bool	Connect(int port) = 0;
	virtual bool	Send_data() = 0;
	virtual bool	Receive_data() = 0;
	virtual bool	is_connected() = 0;
};
