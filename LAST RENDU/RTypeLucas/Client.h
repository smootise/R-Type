#pragma once
#include <iostream>
#include <string>
#include "ITCPSocket.h"
#include "CircularBuff.h"
#include "CommandHandler.h"
#include "Room.h"
#include "IUDPSocket.h"
#include "ClientMessage.h"
#include "Gui.hpp"


/* state values :
Logged => if the client is logged in or not
Pending => if the client is expecting a response to a request
Playing => if the client is in game or not
*/

class Client
{
protected:
	// pre-game related
	std::string						_hostname;
	std::string						_strport;
	ITCPSocket						*_socket;
	CircularBuff					_readbuff;
	CircularBuff					_writebuff;
	Selector						_sel;
	CommandHandler					*_comhandler;
	std::map <std::string, bool>	_state;
	int								_lastcommand;
	std::vector<std::string>		*_availlablerooms;
	Gui							_graphic;							
	//in game related
	IUDPSocket						*_game_socket;
	ClientMessage					*_send_msg;
	ServerMessage					*_recv_msg;

public:
	Client(std::string &hostname, std::string &strport);
	virtual ~Client(void);

	bool	init();
	bool	update();
};

