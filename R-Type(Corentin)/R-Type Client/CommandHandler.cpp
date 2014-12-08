#include "CommandHandler.h"


CommandHandler::CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::map<std::string, bool> &state, int *lastcommand) :
_writebuff(writebuff), _readbuff(readbuff), _state(state), _lastcommand(lastcommand)
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
	_receiptfunctions[LEAVE_ROOM] = &CommandHandler::LeaveRoomeAnswer;
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

}

void	CommandHandler::RemoveAllyAnswer(Message &answer)
{

}

void		CommandHandler::LoginAnswer(Message &answer)
{
	int		rq_type = answer.get_rq_type();
	
	if (rq_type == OK)
	{
		_state["Logged"] = true;
		std::cout << "JE SUIS LOGGED IN" << std::endl;
	}
}

void	CommandHandler::GetRoomsAnswer(Message &answer)
{

}

void	CommandHandler::JoinRoomAnswer(Message &answer)
{

}

void	CommandHandler::LeaveRoomeAnswer(Message &answer)
{

}

void	CommandHandler::CreateRoomAnswer(Message &answer)
{

}

void	CommandHandler::StartGameAnswer(Message &answer)
{

}


// fonctions that send data
void	CommandHandler::SendLogin(std::string *arg)
{
	Message		mess((uint32_t)LOGIN, (uint32_t)(arg->size()), (void *)(arg->c_str()));

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendLogout(std::string *arg)
{
	Message		mess((uint32_t)LOGOUT, (uint32_t)(arg->size()), (void *)(arg->c_str()));

	_writebuff.add_data(mess);
}

void	CommandHandler::SendGetRooms(std::string *arg)
{
	Message		mess((uint32_t)GET_ROOMS, (uint32_t)(arg->size()), (void *)(arg->c_str()));

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendJoinRoom(std::string *arg)
{
	Message		mess((uint32_t)JOIN_ROOM, (uint32_t)(arg->size()), (void *)(arg->c_str()));

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendLeaveRoom(std::string *arg)
{
	Message		mess((uint32_t)LEAVE_ROOM, (uint32_t)(arg->size()), (void *)(arg->c_str()));

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendCreateRoom(std::string *arg)
{
	Message		mess((uint32_t)CREATE_ROOM, (uint32_t)(arg->size()), (void *)(arg->c_str()));

	_writebuff.add_data(mess);
	_state["Pending"] = true;
}

void	CommandHandler::SendStartGame(std::string *arg)
{
	Message		mess((uint32_t)START_GAME, (uint32_t)(arg->size()), (void *)(arg->c_str()));

	_writebuff.add_data(mess);
}