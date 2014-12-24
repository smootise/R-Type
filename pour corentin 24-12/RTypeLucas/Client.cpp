#include <iostream>
#include <string>
#include "Client.h"
#include <stdlib.h> // for sleep A REMOVER

#ifdef _WIN32
	#include "TCPWinSocket.h"
	#include "UDPWinSocket.h"
#else
	#include "TCPLinSocket.h"
	#include "UDPLinSocket.h"
#endif

Client::Client(std::string &hostname, std::string &strport) :
	_hostname(hostname), _strport(strport)
{
	_availlablerooms = new std::vector<std::string>();
	//initialisation of state values
	_state["Logged"] = false;
	_state["Playing"] = false;
	_state["Pending"] = false;

	#ifdef _WIN32
		_socket = new TCPWinSocket();
		_game_socket = new UDPWinSocket(hostname);
	#else
		_socket = new TCPLinSocket();
		_game_socket = new UDPLinSocket(hostname);
	#endif
	_comhandler = new CommandHandler(_writebuff, _readbuff, _state, &_lastcommand, _availlablerooms);
	_lastcommand = 0;
	_send_msg = new ClientMessage;
	_recv_msg = new ServerMessage;
}


Client::~Client(void)
{
	delete _socket;
	delete _comhandler;
	delete _send_msg;
}

bool	Client::init()
{
	if (_graphic.init() == false)
		return (false);
	memset(_send_msg, '\0', sizeof(ClientMessage));
	memset(_recv_msg, '\0', sizeof(ServerMessage));
	return (_socket->ConnectToServer(_hostname, _strport, _sel));
}

bool	Client::update()
{
  int				ret;
	
  //bails en TCP
  if (_state["Playing"] == false)
    {
      _sel.Select();
      _socket->SendData(_writebuff, _sel);
      if ((_socket->ReadData(_readbuff, _sel)) == false)
			return (false);
      _comhandler->ReceiptCommand();
      if ((ret = _graphic.affScreen(_state, _comhandler, _availlablerooms, _comhandler->get_room(), _comhandler->get_name())) == Gui::Error)
      {
      	std::cerr << "graphical error " << std::endl;
      	return (false);
      }
      else if (ret == Gui::Quit)
      	return (false);
    }
  else // bails en UDP
    {
      if (_game_socket->is_connected() == false &&
	  _game_socket->Connect(_comhandler->get_port()) == false)
		{
			_state["Playing"] = true;
			std::cerr << "Error at udp initialisation" << std::endl;
			return (true);
		}
	  else
		  memcpy(_send_msg->name, _comhandler->get_name()->c_str(), _comhandler->get_name()->size());
      _game_socket->Receive_data(_recv_msg);
      _game_socket->Send_data(_send_msg);
	  _graphic.affGame(_recv_msg, _send_msg);
    }
  return (true);
}
