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
	memcpy(_send_msg->name[J1], name_default.c_str(), name_default.size());
	memcpy(_send_msg->name[J2], name_default.c_str(), name_default.size());
	memcpy(_send_msg->name[J3], name_default.c_str(), name_default.size());
	memcpy(_send_msg->name[J4], name_default.c_str(), name_default.size());
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
	if (sendername != std::string(_send_msg->name[J1]) &&
		sendername != std::string(_send_msg->name[J2]) &&
		sendername != std::string(_send_msg->name[J3]) &&
		sendername != std::string(_send_msg->name[J4]))
	{
		if (defaultname == std::string(_send_msg->name[J1]))
		{
			memset(_send_msg->name[J1], '\0', 256);
			memcpy(_send_msg->name[J1], sendername.c_str(), sendername.size());
		}
		else if (defaultname == std::string(_send_msg->name[J2]))
		{
			memset(_send_msg->name[J2], '\0', 256);
			memcpy(_send_msg->name[J2], sendername.c_str(), sendername.size());
		}
		else if (defaultname == std::string(_send_msg->name[J3]))
		{
			memset(_send_msg->name[J3], '\0', 256);
			memcpy(_send_msg->name[J3], sendername.c_str(), sendername.size());
		}
		else if (defaultname == std::string(_send_msg->name[J4]))
		{
			memset(_send_msg->name[J4], '\0', 256);
			memcpy(_send_msg->name[J4], sendername.c_str(), sendername.size());
		}
		else
			std::cerr << "corrupted informations received by the server" << std::endl;
	}
	//on mets ses bails a jours
	if (sendername == std::string(_send_msg->name[J1]))
	{
		_send_msg->direction[J1] = _recv_msg->direction;
		_send_msg->posx[J1] = _recv_msg->posx;
		_send_msg->posy[J1] = _recv_msg->posy;
	}
	else if (sendername == std::string(_send_msg->name[J2]))
	{
		_send_msg->direction[J2] = _recv_msg->direction;
		_send_msg->posx[J2] = _recv_msg->posx;
		_send_msg->posy[J2] = _recv_msg->posy;
	}
	else if (sendername == std::string(_send_msg->name[J3]))
	{
		_send_msg->direction[J3] = _recv_msg->direction;
		_send_msg->posx[J3] = _recv_msg->posx;
		_send_msg->posy[J3] = _recv_msg->posy;
	}
	else
	{
		_send_msg->direction[J4] = _recv_msg->direction;
		_send_msg->posx[J4] = _recv_msg->posx;
		_send_msg->posy[J4] = _recv_msg->posy;
	}
}