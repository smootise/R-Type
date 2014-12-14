#include "Server.h"

#ifdef _WIN32
	#include "TCPWinServSocket.h"
#else
	#include "TCPLinServerSocket.h"
#endif

Server::Server(int port)
	: _port(port) 
{
	#ifdef _WIN32
		_socket = new TCPWinServSocket(_clients);
	#else
		_socket = new TCPLinServerSocket(_clients);
	#endif
	_comhandler = new CommandHandler(_writebuff, _readbuff, _clients, _rooms);
}

Server::~Server(void)
{
	if (_socket != NULL)
		delete _socket;
	delete _comhandler;
}

bool		Server::init(void)
{
	return (_socket->Connect(_port, _sel));
}

bool		Server::update(void)
{
	_sel.Select();
	if (_socket->SearchNewClients(_sel) == false)
		return (false);
	_socket->SendData(_writebuff, _sel);
	_socket->ReadData(_readbuff, _sel);
	_comhandler->ReceiptCommand();
	return (true);
}
