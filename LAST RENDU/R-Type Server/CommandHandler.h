#pragma once
#include <map>
#include <vector>
#include <sstream>
#include "Commands.h"
#include "CircularBuff.h"
#include "Room.h"

#ifdef _WIN32
	#include "WinThread.h"
#else
	#include "LinThread.h"
#endif

class CommandHandler;

typedef void (CommandHandler::*FuncType1)(Message &mess);

class CommandHandler
{
protected:
	CircularBuff					&_writebuff;
	CircularBuff					&_readbuff;
	std::vector<Client>				&_clients;
	std::map<int, FuncType1>		_receiptfunctions;
	std::vector<Room>				&_rooms;
	int								_nextport;

public:
	CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::vector<Client> &clients,
				   std::vector<Room> &rooms);
	virtual ~CommandHandler();

	void	ReceiptCommand();

// Fonctions that analyse incoming requests
protected:
	void	ReceiptLogin(Message &mess);
	void	ReceiptLogout(Message &mess);
	void	ReceiptGetRooms(Message &mess);
	void	ReceiptJoinRoom(Message &mess);
	void	ReceiptLeaveRoom(Message &mess);
	void	ReceiptCreateRoom(Message &mess);
	void	ReceiptStartGame(Message &mess);
};
