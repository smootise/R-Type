#include "CommandHandler.h"


CommandHandler::CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::vector<Client> &clients) :
_writebuff(writebuff), _readbuff(readbuff), _clients(clients)
{
	_receiptfunctions[LOGIN] = &CommandHandler::ReceiptLogin;
	_receiptfunctions[LOGOUT] = &CommandHandler::ReceiptLogout;
	_receiptfunctions[GET_ROOMS] = &CommandHandler::ReceiptGetRooms;
	_receiptfunctions[JOIN_ROOM] = &CommandHandler::ReceiptJoinRoom;
	_receiptfunctions[LEAVE_ROOM] = &CommandHandler::ReceiptLeaveRoom;
	_receiptfunctions[CREATE_ROOM] = &CommandHandler::ReceiptCreateRoom;
	_receiptfunctions[START_GAME] = &CommandHandler::ReceiptStartGame;
}

CommandHandler::~CommandHandler()
{

}

void				CommandHandler::ReceiptCommand(void)
{
	std::vector<Message>		*answers;

	answers = _readbuff.get_data();
	for (size_t i = 0; i < answers->size(); i++)
		(this->*_receiptfunctions[answers->at(i).get_rq_type()])(answers->at(i));
}

//receipt commands
void	CommandHandler::ReceiptLogin(Message &mess)
{
	std::string		wantedname((char *)mess.get_packet());
	int				ret = OK;
	//verrify if the nickname is already in use or not
	for (size_t i = 0; i < _clients.size(); i++)
		if (_clients[i].get_nickname() == wantedname)
			ret = NOK;

	if (mess.get_client().get_nickname() != std::string("DefaultName"))
		ret = NOK;
	
	if (ret == OK)
		mess.get_client().set_nickname(wantedname);

	Message		retmess((uint32_t)ret, (uint32_t)0, (void *)(std::string("").c_str()), mess.get_client());
	_writebuff.add_data(retmess);
}

void	CommandHandler::ReceiptLogout(Message &mess)
{

}

void	CommandHandler::ReceiptGetRooms(Message &mess)
{

}

void	CommandHandler::ReceiptJoinRoom(Message &mess)
{

}

void	CommandHandler::ReceiptLeaveRoom(Message &mess)
{

}

void	CommandHandler::ReceiptCreateRoom(Message &mess)
{

}

void	CommandHandler::ReceiptStartGame(Message &mess)
{

}