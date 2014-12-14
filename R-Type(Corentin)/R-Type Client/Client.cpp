#include <iostream>
#include <string>
#include "Client.h"

#ifdef _WIN32
	#include "TCPWinSocket.h"
#else
	#include "TCPLinSocket.h"
#endif

Client::Client(std::string &hostname, std::string &strport) :
	_hostname(hostname), _strport(strport)
{
	_availlablerooms = new std::vector<std::string>();

	#ifdef _WIN32
		_socket = new TCPWinSocket();
	#else
		_socket = new TCPLinSocket();
	#endif
	_comhandler = new CommandHandler(_writebuff, _readbuff, _state, &_lastcommand, _room, _availlablerooms);

//initialisation of state values
	_state["Logged"] = false;
	_state["Playing"] = false;
	_state["Pending"] = false;
	_lastcommand = 0;
	_room = NULL;
}


Client::~Client(void)
{
	delete _socket;
	delete _comhandler;
	if (_room)
		delete _room;
}

bool	Client::init()
{
	return (_socket->ConnectToServer(_hostname, _strport, _sel));
}

bool	Client::update()
{
	std::string		line;
	int				rq_type;

	std::getline(std::cin, line);
	rq_type = atoi(line.substr(0, 1).c_str());
	if (rq_type != 0)
	{
		std::string		*str = new std::string(line.substr(1, std::string::npos));
		_comhandler->SendCommand(rq_type, str);
	}
	_sel.Select();
	_socket->SendData(_writebuff, _sel);
	if ((_socket->ReadData(_readbuff, _sel)) == false)
		return (false);
	_comhandler->ReceiptCommand();
	return (true);
}
