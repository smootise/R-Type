#pragma once
#include <iostream>
#include <string>

#ifdef _WIN32
	#include "UDPWinServSocket.h"
#else
	#include "UDPLinServSocket.h"
#endif

#include "Client.h"
#include "ServerMessage.h"
#include "Spawner.h"
#include "ClockObj.h"

class IThread
{
public:
	virtual ~IThread() {}

	virtual bool	start() = 0;
	virtual bool	run() = 0;
};