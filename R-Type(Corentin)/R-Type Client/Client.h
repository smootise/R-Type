#pragma once
#include <iostream>
#include <string>
#include "ITCPSocket.h"
#include "CircularBuff.h"

class Client
{
protected:
	std::string		_hostname;
	std::string		_strport;
	ITCPSocket		*_socket;
	CircularBuff	_readbuff;
	CircularBuff	_writebuff;
	Selector		_sel;

public:
	Client(std::string &hostname, std::string &strport);
	virtual ~Client(void);

	bool	init();
	bool	update();
};

