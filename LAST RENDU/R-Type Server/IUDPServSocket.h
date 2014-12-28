#pragma once
#include <iostream>
#include <string>

#include "ClientMessage.h"
#include "ServerMessage.h"

class IUDPServSocket
{
public :
	virtual ~IUDPServSocket() {}

	virtual bool	Connect(int port) = 0;
	virtual bool	Receive_data(ClientMessage *, ServerMessage *) = 0;
protected:
	virtual bool	send_data(struct sockaddr_in *target, ServerMessage *) = 0;
};