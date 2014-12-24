#pragma once
#include <map>
#include <stdlib.h>
#include "Commands.h"
#include "CircularBuff.h"
#include "Room.h"

class CommandHandler;

typedef void (CommandHandler::*FuncType1)(char *arg, int arglen);
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
  int								_wantedport;

 public:
  CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::map<std::string, bool> &state,
		 int *lastcommand, std::vector<std::string> *availlablerooms);
  virtual ~CommandHandler();

  void	SendCommand(int value, std::string &arg);
  void	ReceiptCommand();

  //sendcommands
 protected:
  void	SendLogin(char *arg, int arglen);
  void	SendLogout(char *arg, int arglen);
  void	SendGetRooms(char *arg, int arglen);
  void	SendJoinRoom(char *arg, int arglen);
  void	SendLeaveRoom(char *arg, int arglen);
  void	SendCreateRoom(char *arg, int arglen);
  void	SendStartGame(char *arg, int arglen);

  //receiptcommands
  void	AddAllyAnswer(Message &answer);
  void	RemoveAllyAnswer(Message &answer);
  void	LoginAnswer(Message &answer);
  void	GetRoomsAnswer(Message &answer);
  void	JoinRoomAnswer(Message &answer);
  void	LeaveRoomAnswer(Message &answer);
  void	CreateRoomAnswer(Message &answer);
  void	StartGameAnswer(Message &answer);
  void	GameStartedAnswer(Message &answer);

 public:
  Room		*get_room() const;
  std::string	*get_name() const;
  int			 get_port() const;
};

