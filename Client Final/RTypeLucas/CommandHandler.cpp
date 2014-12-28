#include "CommandHandler.h"


CommandHandler::CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::map<std::string, bool> &state, int *lastcommand,
	 std::vector<std::string> *availlablerooms) :
	_writebuff(writebuff), _readbuff(readbuff), _state(state), _lastcommand(lastcommand), _availlablerooms(availlablerooms)
{
	_sendfunctions[LOGIN] = &CommandHandler::SendLogin;
	_sendfunctions[LOGOUT] = &CommandHandler::SendLogout;
	_sendfunctions[GET_ROOMS] = &CommandHandler::SendGetRooms;
	_sendfunctions[JOIN_ROOM] = &CommandHandler::SendJoinRoom;
	_sendfunctions[LEAVE_ROOM] = &CommandHandler::SendLeaveRoom;
	_sendfunctions[CREATE_ROOM] = &CommandHandler::SendCreateRoom;
	_sendfunctions[START_GAME] = &CommandHandler::SendStartGame;

	_receiptfunctions[LOGIN] = &CommandHandler::LoginAnswer;
	_receiptfunctions[GET_ROOMS] = &CommandHandler::GetRoomsAnswer;
	_receiptfunctions[JOIN_ROOM] = &CommandHandler::JoinRoomAnswer;
	_receiptfunctions[LEAVE_ROOM] = &CommandHandler::LeaveRoomAnswer;
	_receiptfunctions[CREATE_ROOM] = &CommandHandler::CreateRoomAnswer;
	_receiptfunctions[START_GAME] = &CommandHandler::StartGameAnswer;
	_receiptfunctions[ADD_ALLY] = &CommandHandler::AddAllyAnswer;
	_receiptfunctions[REMOVE_ALLY] = &CommandHandler::RemoveAllyAnswer;
	_receiptfunctions[GAME_STARTED] = &CommandHandler::GameStartedAnswer;

	_name = NULL;
	_room = NULL;
}

CommandHandler::~CommandHandler()
{
	if (_room)
		delete _room;
	if (_name)
		delete _name;
}

void	CommandHandler::SendCommand(int value, std::string &arg)
{
	
	if (_state["Logged"] == false && value != LOGIN)
	{
		std::cout << " le client essaye d'envoyer une commande sans être logged in" << std::endl;
		return ;
	}
	// to verrify that he is not currently waiting for server answer
	if (_state["Pending"] == false)
	{
		if (arg == std::string(""))
			(this->*_sendfunctions[value])(NULL, 0);
		else
		{
			int		len = arg.size();
			char	*param = new char[len + 1];

			memcpy(param, arg.c_str(), len + 1);
			(this->*_sendfunctions[value])(param, len);
		}
		*_lastcommand = value;
	}
}

void							CommandHandler::ReceiptCommand(void)
{
	std::vector<Message>		&answers = _readbuff.get_data();

	for (size_t i = 0; i < answers.size(); i++)
	{
		// If answers are OK/NOK we use the _lastcommand to determine the function.
		// Else we use the rq_type.
		if (answers.at(i).get_rq_type() == OK || answers.at(i).get_rq_type() == NOK)
		{	
			if (*_lastcommand != NONE)
				(this->*_receiptfunctions[*_lastcommand])(answers.at(i));
			else
				std::cerr << "Corrupted answer received from server " << std::endl;
			*_lastcommand = NONE;
			_state["Pending"] = false;
		}
		else if (answers.at(i).get_rq_type() == REMOVE_ALLY || answers.at(i).get_rq_type() == ADD_ALLY || answers.at(i).get_rq_type() == GAME_STARTED)
			(this->*_receiptfunctions[answers.at(i).get_rq_type()])(answers.at(i));
		else
			std::cerr << "INVALID ANSWER RECEVEID FROM THE SERVER" << std::endl;
		delete[]	answers.at(i).get_packet();
	}
	answers.clear();
}


// fonctions that analyse received data
void	CommandHandler::AddAllyAnswer(Message &answer)
{
	std::string		allyname(answer.get_packet());

	if (_room != NULL)
		_room->Add_Ally(allyname);
	else
		std::cerr << "Server message is corrupted (1)" << std::endl;

	//debug
	_room->To_String();
}

void	CommandHandler::RemoveAllyAnswer(Message &answer)
{
	std::string		allyname(answer.get_packet());

	if (_room != NULL)
		_room->Remove_Ally(allyname);
	else
		std::cerr << "Server message is corrupted (2)" << std::endl;

	//debug
	_room->To_String();
}

void		CommandHandler::LoginAnswer(Message &answer)
{
	int		rq_type = answer.get_rq_type();
	
	if (rq_type == OK)
	{
		_state["Logged"] = true;
		_name = new std::string(answer.get_packet());
	}
}

void				CommandHandler::GetRoomsAnswer(Message &answer)
{
	int				rq_type = answer.get_rq_type();
	std::string		roomanswer(answer.get_packet());
	int				pos_start = 0;
	int				pos_end = 0;
	int				ret;

	if (rq_type == OK && roomanswer.size() != 0)
	{
		_availlablerooms->clear();
		ret = -1;
		while ((ret = roomanswer.find("|", ret + 1)) != std::string::npos)
		{	
			pos_end = ret;
			_availlablerooms->push_back(roomanswer.substr(pos_start, pos_end - pos_start));
			pos_start = pos_end + 1;
		}
		_availlablerooms->push_back(roomanswer.substr(pos_start));
	}
}

void	CommandHandler::JoinRoomAnswer(Message &answer)
{
  std::string		roomname(answer.get_packet());

  if (answer.get_rq_type() == OK)
    {
      _room = new Room(roomname);
      //debug
      _room->To_String();
    }
}

void	CommandHandler::LeaveRoomAnswer(Message &answer)
{
	if (answer.get_rq_type() == OK)
	{
		delete _room;
		_room = NULL;
	}
}

void	CommandHandler::CreateRoomAnswer(Message &answer)
{	
  std::string		roomname(answer.get_packet());

  if (answer.get_rq_type() == OK)
    {
      _room = new Room(roomname);
      //debug
      _room->To_String();
    }
}

void	CommandHandler::StartGameAnswer(Message &answer)
{

}

void	CommandHandler::GameStartedAnswer(Message &answer)
{
	_state["Playing"] = true;
	_wantedport = atoi(answer.get_packet());
}


// fonctions that send data
void	CommandHandler::SendLogin(char *arg, int arglen)
{
	Message		mess(LOGIN, arglen, arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendLogout(char *arg, int arglen)
{
	Message		mess(LOGOUT, arglen, arg);

	_writebuff.add_data(mess);
}

void	CommandHandler::SendGetRooms(char *arg, int arglen)
{
	Message		mess(GET_ROOMS, arglen, arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendJoinRoom(char *arg, int arglen)
{
	Message		mess(JOIN_ROOM, arglen, arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendLeaveRoom(char *arg, int arglen)
{
	int		len = _room->get_name().size();
	char	*roomname = new char[len + 1];

	memcpy(roomname, _room->get_name().c_str(), len + 1); 
	Message		mess(LEAVE_ROOM, len, roomname);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendCreateRoom(char *arg, int arglen)
{
	Message		mess(CREATE_ROOM, arglen, arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendStartGame(char *arg, int arglen)
{
	Message		mess(START_GAME, arglen, arg);

	_writebuff.add_data(mess);
}
	
Room			*CommandHandler::get_room() const
{
	return (_room);
}

std::string		*CommandHandler::get_name() const
{
	return (_name);
}

int				CommandHandler::get_port() const
{
	return (_wantedport);
}
