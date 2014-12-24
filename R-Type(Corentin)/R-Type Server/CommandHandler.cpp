#include "CommandHandler.h"


CommandHandler::CommandHandler(CircularBuff &writebuff, CircularBuff &readbuff, std::vector<Client> &clients,
								std::vector<Room> &rooms) :
	_writebuff(writebuff), _readbuff(readbuff), _clients(clients), _rooms(rooms), _nextport(4243)
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
	std::vector<Message>		&answers = _readbuff.get_data();

	for (size_t i = 0; i < answers.size(); i++)
	{
		(this->*_receiptfunctions[answers.at(i).get_rq_type()])(answers.at(i));
		delete[]	answers.at(i).get_packet();
	}
	answers.clear();
}


//receipt commands
void	CommandHandler::ReceiptLogin(Message &mess)
{
	std::string		wantedname(mess.get_packet());
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
	int			len = wantedname.size();
	char		*name = new char[len + 1];

	memcpy(name, wantedname.c_str(), len + 1);

	Message		retmess(ret, len, name, mess.get_client());
	_writebuff.add_data(retmess);
}

void	CommandHandler::ReceiptLogout(Message &mess)
{
	// For now this isn't used.
}

void				CommandHandler::ReceiptGetRooms(Message &mess)
{
	std::string		roomlist;

	for (size_t i = 0; i < _rooms.size(); i++)
	{
		if (i != 0)
			roomlist.append("|");
		roomlist.append(_rooms.at(i).Get_Name().c_str());
	}
	int			len = roomlist.size();
	char		*packet = new char[len + 1];

	memcpy(packet, roomlist.c_str(), len + 1);
	Message		retmess(OK, len, packet, mess.get_client());
	_writebuff.add_data(retmess);
}

void				CommandHandler::ReceiptJoinRoom(Message &mess)
{
	std::string		wantedroom(mess.get_packet());
	int				ret = NOK;
	size_t			id;

	for (size_t i = 0; i < _rooms.size(); i++)
		if (_rooms[i].Get_Name() == wantedroom && _rooms[i].Get_Nb_People() < 4)
		{
			ret = OK;
			id = i;
		}

	//we send response to the client that wanted to join
	int				len = wantedroom.size();
	char			*packet = new char[len + 1];

	memcpy(packet, wantedroom.c_str(), len + 1);
	Message			retmess(ret, len, packet, mess.get_client());
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
  std::string		wantedroom(mess.get_packet());
  int				ret = NOK;
  std::string		Default("DefaultName");

  for (size_t i = 0; i < _rooms.size(); i++)
    if (_rooms[i].Get_Name() == wantedroom)
      {
		_rooms[i].Remove_Ally(mess.get_client(), _writebuff);
		mess.get_client().set_room(Default);
		ret = OK;
      }
  if (ret == NOK)
    {
      Message		newmess(ret, 0, NULL, mess.get_client());
      _writebuff.add_data(newmess);
    }
}

void				CommandHandler::ReceiptCreateRoom(Message &mess)
{
	std::string		wantedroom(mess.get_packet());
	int				ret = OK;

	for (size_t i = 0; i < _rooms.size(); i++)
		if (_rooms[i].Get_Name() == wantedroom)
			ret = NOK;

	int				len = wantedroom.size();
	char			*packet = new char[len + 1];

	memcpy(packet, wantedroom.c_str(), len + 1);
	Message			retmess(ret, len, packet, mess.get_client());
	
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
  int	ret = NOK;

  if (mess.get_client().get_room() == std::string("DefaultName"))
    {
      std::cerr << "un client n'etant pas dans une room veut start" << std::endl;
      Message		retmess(ret, 0, NULL, mess.get_client());
      _writebuff.add_data(retmess);
      return ;
    }

  for (size_t i = 0; i < _clients.size(); i++)
    if (mess.get_client().get_room() == _clients[i].get_room())
      {
		std::ostringstream		oss;
		oss << _nextport;
	
		int				len = oss.str().size();
		char			*port = new char[len + 1];

		memcpy(port, oss.str().c_str(), len + 1);
		Message			retmess(GAME_STARTED, len, port, _clients.at(i));
			
		_writebuff.add_data(retmess);
		ret = OK;
      }
  Message		retmess(ret, 0, NULL, mess.get_client());
  _writebuff.add_data(retmess);
  if (ret == OK)
    {
#ifdef _WIN32
      IThread		*T1 = new WinThread(_nextport);
      _beginthread(&WinThread::call_run, 0, T1);
#else
      IThread		*T1 = new LinThread(_nextport);
      pthread_t		thread;

      pthread_create(&thread, NULL, &LinThread::call_run, T1);
#endif
      //lancer les threads
      _nextport++;
    }
}
