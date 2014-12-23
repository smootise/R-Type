#pragma once

#include <string>
#include <iostream>
#include "ClientMessage.h"
#include "ServerMessage.h"

class IUDPSocket
{
public:
	virtual ~IUDPSocket() {}

	virtual bool	Connect(int port) = 0;
	virtual bool	Send_data(ClientMessage *) = 0;
	virtual bool	Receive_data(ServerMessage *) = 0;
	virtual bool	is_connected() = 0;
};
