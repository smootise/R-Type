#include "CommandHandler.h"


CommandHandler::CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::vector<Client> &clients,
								std::vector<Room> &rooms) :
	_writebuff(writebuff), _readbuff(readbuff), _clients(clients), _rooms(rooms)
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
	delete answers;
}


//receipt commands
void	CommandHandler::ReceiptLogin(Message &mess)
{
	std::string		wantedname((char *)(mess.get_packet()));
	int				ret = OK;

	//verrify if the nickname is already in use or not
	for (size_t i = 0; i < _clients.size(); i++)
		if (_clients[i].get_nickname() == wantedname)
			ret = NOK;

	if (mess.get_client().get_nickname() != std::string("DefaultName") || wantedname == std::string(""))
		ret = NOK;
	
	if (ret == OK)
	{
		mess.get_client().set_nickname(wantedname);
		std::cout << "desormais ton nom est : " << wantedname << std::endl;
	}
	std::string	*str = new std::string(wantedname);

	Message		retmess((uint32_t)ret, (uint32_t)(str->size()), (void *)(str->c_str()), str, mess.get_client());
	_writebuff.add_data(retmess);
}

void	CommandHandler::ReceiptLogout(Message &mess)
{
	// For now this isn't used.
}

void				CommandHandler::ReceiptGetRooms(Message &mess)
{
	std::string		*roomlist;

	roomlist = new std::string();
	for (size_t i = 0; i < _rooms.size(); i++)
	{
		if (i != 0)
			roomlist->append("|");
		roomlist->append(_rooms.at(i).Get_Name().c_str());
	}
	
	Message		retmess((uint32_t)OK, (uint32_t)(roomlist->size()), (void *)(roomlist->c_str()), roomlist, mess.get_client());
	_writebuff.add_data(retmess);
}

void				CommandHandler::ReceiptJoinRoom(Message &mess)
{
	std::string		wantedroom((char *)mess.get_packet());
	int				ret = NOK;
	size_t			id;

	for (size_t i = 0; i < _rooms.size(); i++)
		if (_rooms[i].Get_Name() == wantedroom && _rooms[i].Get_Nb_People() < 4)
		{
			ret = OK;
			id = i;
		}

	//we send response to the client that wanted to join
	std::string		*str = new std::string((char *)mess.get_packet());
	Message			retmess((uint32_t)ret, (uint32_t)(str->size()), (void *)(str->c_str()), str, mess.get_client());
	_writebuff.add_data(retmess);

	if (ret == OK)
	{
		//we add the client to the room
		//we send to this client all other people in this room
		//we send to all other people in the room his arrival.
		//All 3 are done in the room's add_ally method
		_rooms[id].Add_Ally(mess.get_client(), _writebuff);

		// we add the room to the client 
		mess.get_client().set_room(wantedroom);
	}
}

void	CommandHandler::ReceiptLeaveRoom(Message &mess)
{
	std::string		wantedroom((char *)mess.get_packet());
	int				ret = NOK;

	for (size_t i = 0; i < _rooms.size(); i++)
		if (_rooms[i].Get_Name() == wantedroom)
		{
			_rooms[i].Remove_Ally(mess.get_client(), _writebuff);
			mess.get_client().set_room(std::string("DefaultName"));
			ret = OK;
		}
	if (ret == NOK)
	{
		Message		newmess((uint32_t)ret, (uint32_t)0, (void *)(std::string("").c_str()), NULL, mess.get_client());
		_writebuff.add_data(newmess);
	}
}

void				CommandHandler::ReceiptCreateRoom(Message &mess)
{
	std::string		wantedroom((char *)mess.get_packet());
	int				ret = OK;

	for (size_t i = 0; i < _rooms.size(); i++)
		if (_rooms[i].Get_Name() == wantedroom)
			ret = NOK;

	std::string		*str = new std::string((char *)mess.get_packet());
	Message			retmess((uint32_t)ret, (uint32_t)(str->size()), (void *)(str->c_str()), str, mess.get_client());
	_writebuff.add_data(retmess);

	if (ret == OK)
	{
		Room	newroom(wantedroom);

		//we add the client to the room
		newroom.Add_Ally(mess.get_client(), _writebuff);
		//we add the room to the client
		mess.get_client().set_room(wantedroom);
		_rooms.push_back(newroom);
	}
}

void	CommandHandler::ReceiptStartGame(Message &mess)
{

}