#pragma once
#include <iostream>
#include <string>
#include "CircularBuff.h"
#include "Selector.h"

class ITCPSocket
{
public :
	virtual ~ITCPSocket() {}
	
	virtual bool	ConnectToServer(std::string &hostname, std::string port, Selector &sel) = 0;
	virtual bool	ReadData(CircularBuff &buff, Selector &sel) = 0;
	virtual void	SendData(CircularBuff &buff, Selector &sel) = 0;
};