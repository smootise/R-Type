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
	#ifdef _WIN32
		_socket = new TCPWinSocket();
	#else
		_socket = new TCPLinSocket();
	#endif
	_comhandler = new CommandHandler(_writebuff, _readbuff, _state, &_lastcommand);

//initialisation of state values
	_state["Logged"] = false;
	_state["Playing"] = false;
	_state["Pending"] = false;
	_lastcommand = 0;
}


Client::~Client(void)
{
	delete _socket;
	delete _comhandler;
}

bool	Client::init()
{
	return (_socket->ConnectToServer(_hostname, _strport, _sel));
}

bool	Client::update()
{
	std::string		line;
	int				rq_type;

	_sel.Select();
	std::getline(std::cin, line);
	if (line != std::string("next"))
	{
		rq_type = atoi(line.c_str());
		_comhandler->SendCommand(rq_type, new std::string("Default"));
	}
	_socket->SendData(_writebuff, _sel);
	if ((_socket->ReadData(_readbuff, _sel)) == false)
		return (false);
	_comhandler->ReceiptCommand();
	return (true);
}
