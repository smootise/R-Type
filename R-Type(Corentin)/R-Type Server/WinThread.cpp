#include "WinThread.h"


WinThread::WinThread(int port) : _port(port)
{

}


WinThread::~WinThread()
{

}

bool	WinThread::start()
{
	std::string		name_default("DefaultName");

	_socket = new UDPWinServSocket();
	if (_socket->Connect(_port) == false)
		return (false);
	_recv_msg = new ClientMessage;
	memset(_recv_msg, '\0', sizeof(ClientMessage));
	_recv_msg->has_been_read = true;

	_send_msg = new ServerMessage;
	memset(_send_msg, '\0', sizeof(ServerMessage));
	memcpy(_send_msg->nameA, name_default.c_str(), name_default.size());
	memcpy(_send_msg->nameB, name_default.c_str(), name_default.size());
	memcpy(_send_msg->nameC, name_default.c_str(), name_default.size());
	memcpy(_send_msg->nameD, name_default.c_str(), name_default.size());
	return (true);
}

bool	WinThread::run()
{
	while (42)
	{
		_socket->Receive_data(_recv_msg, _send_msg);
		this->analyse_data();
	}
	return (false);
}

void	WinThread::call_run(void *ptr)
{
	WinThread		*T;
	T = reinterpret_cast<WinThread *>(ptr);

	if (T->start() == true)
		T->run();
}

void				WinThread::analyse_data()
{
	std::string		sendername(_recv_msg->name);
	std::string		defaultname("DefaultName");

	if (_recv_msg->has_been_read == true)
		return;
	_recv_msg->has_been_read = true;
	//s'il n'existe pas on l'ajoute
	if (sendername != std::string(_send_msg->nameA) &&
		sendername != std::string(_send_msg->nameB) &&
		sendername != std::string(_send_msg->nameC) &&
		sendername != std::string(_send_msg->nameD))
	{
		if (defaultname == std::string(_send_msg->nameA))
		{
			std::cout << "je clean le 1er" << std::endl;
			memset(_send_msg->nameA, '\0', 256);
			memcpy(_send_msg->nameA, sendername.c_str(), sendername.size());
		}
		else if (defaultname == std::string(_send_msg->nameB))
		{
			std::cout << "je clean le second" << std::endl;
			memset(_send_msg->nameB, '\0', 256);
			memcpy(_send_msg->nameB, sendername.c_str(), sendername.size());
		}
		else if (defaultname == std::string(_send_msg->nameC))
		{
			memset(_send_msg->nameC, '\0', 256);
			memcpy(_send_msg->nameC, sendername.c_str(), sendername.size());
		}
		else if (defaultname == std::string(_send_msg->nameD))
		{
			memset(_send_msg->nameD, '\0', 256);
			memcpy(_send_msg->nameD, sendername.c_str(), sendername.size());
		}
		else
			std::cerr << "corrupted informations received by the server" << std::endl;
	}
	//on mets ses bails a jours
	if (sendername == std::string(_send_msg->nameA))
	{
		_send_msg->directionA = _recv_msg->direction;
		_send_msg->posxA = _recv_msg->posx;
		_send_msg->posyA = _recv_msg->posy;
	}
	else if (sendername == std::string(_send_msg->nameB))
	{
		_send_msg->directionB = _recv_msg->direction;
		_send_msg->posxB = _recv_msg->posx;
		_send_msg->posyB = _recv_msg->posy;
	}
	else if (sendername == std::string(_send_msg->nameC))
	{
		_send_msg->directionC = _recv_msg->direction;
		_send_msg->posxC = _recv_msg->posx;
		_send_msg->posyC = _recv_msg->posy;
	}
	else
	{
		_send_msg->directionD = _recv_msg->direction;
		_send_msg->posxD = _recv_msg->posx;
		_send_msg->posyD = _recv_msg->posy;
	}
}