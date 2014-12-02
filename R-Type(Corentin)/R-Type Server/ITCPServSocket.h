#pragma once
#include <iostream>
#include <string>
#include "CircularBuff.h"
#include "Selector.h"

class ITCPServSocket
{
public :
	virtual ~ITCPServSocket() {}
	
	virtual bool	Connect(int port, Selector &sel) = 0;
	virtual bool	SearchNewClients(Selector &sel) = 0;
	virtual void	ReadData(CircularBuff &buff, Selector &sel) = 0;
	virtual void	SendData(CircularBuff &buff, Selector &sel) = 0;
};