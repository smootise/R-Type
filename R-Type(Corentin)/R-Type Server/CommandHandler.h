#pragma once
#include <map>
#include <vector>
#include "Commands.h"
#include "CircularBuff.h"

class CommandHandler;

typedef void (CommandHandler::*FuncType1)(Message &mess);

class CommandHandler
{
protected:
	CircularBuff					&_writebuff;
	CircularBuff					&_readbuff;
	std::vector<Client>				&_clients;
	std::map<int, FuncType1>		_receiptfunctions;

public:
	CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::vector<Client> &clients);
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