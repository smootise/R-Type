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
}


Client::~Client(void)
{
	delete _socket;
}

bool	Client::init()
{
	return (_socket->ConnectToServer(_hostname, _strport, _sel));
}

bool	Client::update()
{
	std::string		line;
	std::string		*test = new std::string("toto");
	Message			mess(1, 4, (void *)(test->c_str())); 

	_sel.Select();
	std::getline(std::cin, line);
	
	_writebuff.add_data(mess);
	_socket->SendData(_writebuff, _sel);
	if ((_socket->ReadData(_readbuff, _sel)) == false)
		return (false);
	return (true);
}
