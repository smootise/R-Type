#include "CommandHandler.h"


CommandHandler::CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::map<std::string, bool> &state, int *lastcommand,
								Room *room, std::vector<std::string> *availlablerooms) :
			_writebuff(writebuff), _readbuff(readbuff), _state(state), _lastcommand(lastcommand), _room(room), _availlablerooms(availlablerooms)
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
}

CommandHandler::~CommandHandler()
{
	
}

void	CommandHandler::SendCommand(int value, std::string *arg)
{
	
	if (_state["Logged"] == false && value != LOGIN)
	{
		std::cout << " le client essaye d'envoyer une commande sans être logged in" << std::endl;
		return ;
	}
	// to verrify that he is not currently waiting for server answer
	if (_state["Pending"] == false)
	{
		(this->*_sendfunctions[value])(arg);
		*_lastcommand = value;
	}
}

void							CommandHandler::ReceiptCommand(void)
{
	std::vector<Message>		*answers;

	answers = _readbuff.get_data();
	for (size_t i = 0; i < answers->size(); i++)
	{
		// If answers are OK/NOK we use the _lastcommand to determine the function.
		// Else we use the rq_type.
		if (answers->at(i).get_rq_type() == OK || answers->at(i).get_rq_type() == NOK)
		{	
			if (*_lastcommand != NONE)
				(this->*_receiptfunctions[*_lastcommand])(answers->at(i));
			else
				std::cerr << "Corrupted answer received from server " << std::endl;
			*_lastcommand = NONE;
			_state["Pending"] = false;
		}
		else if (answers->at(i).get_rq_type() == REMOVE_ALLY || answers->at(i).get_rq_type() == ADD_ALLY)
			(this->*_receiptfunctions[answers->at(i).get_rq_type()])(answers->at(i));
		else
			std::cerr << "INVALID ANSWER RECEVEID FROM THE SERVER" << std::endl;
	}
}


// fonctions that analyse received data
void	CommandHandler::AddAllyAnswer(Message &answer)
{
	std::string		allyname((char *)answer.get_packet());

	if (_room != NULL)
		_room->Add_Ally(allyname);
	else
		std::cerr << "Server message is corrupted (1)" << std::endl;

	//debug
	_room->To_String();
}

void	CommandHandler::RemoveAllyAnswer(Message &answer)
{
	std::string		allyname((char *)answer.get_packet());

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
		std::cout << "Je suis logged in !" << std::endl;
	}
}

void				CommandHandler::GetRoomsAnswer(Message &answer)
{
	int				rq_type = answer.get_rq_type();
	std::string		roomanswer((char *)answer.get_packet());
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
	if (answer.get_rq_type() == OK)
	{
		_room = new Room(std::string((char *)answer.get_packet()));
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
	if (answer.get_rq_type() == OK)
	{
		_room = new Room(std::string((char *)answer.get_packet()));
		//debug
		_room->To_String();
	}
}

void	CommandHandler::StartGameAnswer(Message &answer)
{

}


// fonctions that send data
void	CommandHandler::SendLogin(std::string *arg)
{
	Message		mess((uint32_t)LOGIN, (uint32_t)(arg->size()), (void *)(arg->c_str()), arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendLogout(std::string *arg)
{
	Message		mess((uint32_t)LOGOUT, (uint32_t)(arg->size()), (void *)(arg->c_str()), arg);

	_writebuff.add_data(mess);
}

void	CommandHandler::SendGetRooms(std::string *arg)
{
	Message		mess((uint32_t)GET_ROOMS, (uint32_t)(arg->size()), (void *)(arg->c_str()), arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendJoinRoom(std::string *arg)
{
	Message		mess((uint32_t)JOIN_ROOM, (uint32_t)(arg->size()), (void *)(arg->c_str()), arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendLeaveRoom(std::string *arg)
{
	std::string	*str = new std::string(_room->get_name());
	Message		mess((uint32_t)LEAVE_ROOM, (uint32_t)(str->size()), (void *)(str->c_str()), str);

	delete arg;
	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendCreateRoom(std::string *arg)
{
	Message		mess((uint32_t)CREATE_ROOM, (uint32_t)(arg->size()), (void *)(arg->c_str()), arg);

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendStartGame(std::string *arg)
{
	Message		mess((uint32_t)START_GAME, (uint32_t)(arg->size()), (void *)(arg->c_str()), arg);

	_writebuff.add_data(mess);
}