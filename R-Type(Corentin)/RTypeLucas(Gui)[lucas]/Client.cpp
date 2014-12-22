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
}


Client::~Client(void)
{
	delete _socket;
	delete _comhandler;
}

bool	Client::init()
{
	//if (_graphic.init() == false)
	//	return (false);
	return (_socket->ConnectToServer(_hostname, _strport, _sel));
}

bool	Client::update()
{
  std::string		line;
  int				rq_type;
  //int				ret;
	
  //bails en TCP
  if (_state["Playing"] == false)
    {
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
      //if ((ret = _graphic.affScreen(_state, _comhandler, _availlablerooms, _comhandler->get_room(), _comhandler->get_name())) == Gui::Error)
      //{
      //	std::cerr << "graphical error " << std::endl;
      //	return (false);
      //}
      //else if (ret == Gui::Quit)
      //	return (false);
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
      _game_socket->Receive_data();
      _game_socket->Send_data();
#ifdef _WIN32
      Sleep(1000);
#else
      sleep(1);
#endif
    }
  return (true);
}
