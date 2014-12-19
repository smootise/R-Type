#pragma once
#include <map>
#include "Commands.h"
#include "CircularBuff.h"
#include "Room.h"

class CommandHandler;

typedef void (CommandHandler::*FuncType1)(std::string *arg);
typedef void (CommandHandler::*FuncType2)(Message &answer);

class CommandHandler
{
protected:
	CircularBuff					&_writebuff;
	CircularBuff					&_readbuff;
	std::map<int, FuncType1>		_sendfunctions;
	std::map<int, FuncType2>		_receiptfunctions;
	std::map<std::string, bool>		&_state;
	int								*_lastcommand;
	Room							*_room;
	std::vector<std::string>		*_availlablerooms;
	std::string						*_name;

public:
	CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::map<std::string, bool> &state,
					int *lastcommand, Room *room, std::vector<std::string> *availlablerooms, std::string *name);
	virtual ~CommandHandler();

	void	SendCommand(int value, std::string *arg);
	void	ReceiptCommand();

//sendcommands
protected:
	void	SendLogin(std::string *arg);
	void	SendLogout(std::string *arg);
	void	SendGetRooms(std::string *arg);
	void	SendJoinRoom(std::string *arg);
	void	SendLeaveRoom(std::string *arg);
	void	SendCreateRoom(std::string *arg);
	void	SendStartGame(std::string *arg);

//receiptcommands
	void	AddAllyAnswer(Message &answer);
	void	RemoveAllyAnswer(Message &answer);
	void	LoginAnswer(Message &answer);
	void	GetRoomsAnswer(Message &answer);
	void	JoinRoomAnswer(Message &answer);
	void	LeaveRoomAnswer(Message &answer);
	void	CreateRoomAnswer(Message &answer);
	void	StartGameAnswer(Message &answer);
};

