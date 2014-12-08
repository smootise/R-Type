#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "CommandHandler.h"
#include "ITCPServSocket.h"
#include "CircularBuff.h"

class Server
{
protected:
	int							_port;
	ITCPServSocket				*_socket;
	CircularBuff				_readbuff;
	CircularBuff				_writebuff;
	Selector					_sel;
	std::vector<Client>			_clients;
	CommandHandler				*_comhandler;

public:
	Server(int port);
	virtual ~Server(void);

	bool	init();
	bool	update();
};

