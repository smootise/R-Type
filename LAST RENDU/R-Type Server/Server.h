#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "CommandHandler.h"
#include "ITCPServSocket.h"
#include "CircularBuff.h"
#include "Room.h"

class Server
{
protected:
	int							_port;
	ITCPServSocket				*_socket;
	CircularBuff				_readbuff;
	CircularBuff				_writebuff;
	Selector					_sel;
	std::vector<Client>			_clients;
	std::vector<Room>			_rooms;
	CommandHandler				*_comhandler;

public:
	Server(int port);
	virtual ~Server(void);

	bool	init();
	bool	update();
};

