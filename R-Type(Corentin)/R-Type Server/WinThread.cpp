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

	for (size_t i = 0; i < 100; i++)
		for (size_t j = 0; j < 6; j++)
			_send_msg->shots[i][j] = -1;

	_send_msg->is_game_over = false;
	//we start at lvl1
	_spawner.LoadMonsters("Level1.txt");
	return (true);
}

bool		WinThread::run()
{
	bool	first = false;

	while (true)
	{
		if (_spawner.is_over() == false) // si on joue
			_spawner.update(_start_clock.getElapsedTime(), _diff_clock.getElapsedTime(), _send_msg);
		else // si c'est fini
		{
			if (first == false)
			{
				_start_clock.restart();
				first = true;
			}
			else if ((_start_clock.getElapsedTime() / 1000000) > 10) // si ca fait plus de 10 secondes
				return (false);
		}
		_diff_clock.restart();
		_socket->Receive_data(_recv_msg, _send_msg);
		this->analyse_data();
	}
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

	//s'il existe on lui mets ses infos a jours
	for (size_t i = J1; i <= J4; i++)
		if (sendername == std::string(_send_msg->name[i]))
		{
			_send_msg->direction[i] = _recv_msg->direction;
			_send_msg->posx[i] = _recv_msg->posx;
			_send_msg->posy[i] = _recv_msg->posy;
			if (_recv_msg->current_coldown < _send_msg->current_cd[i])
				_spawner.create_shot(ALLY, 3, _recv_msg->posx, _recv_msg->posy, 10, 0);
			_send_msg->current_cd[i] = _recv_msg->current_coldown;
			return ;
		}
	//s'il n'existe pas on l'ajoute
	for (size_t i = J1; i <= J4; i++)
		if (defaultname == std::string(_send_msg->name[i]))
		{
			memset(_send_msg->name[i], '\0', 256);
			memcpy(_send_msg->name[i], sendername.c_str(), sendername.size());
			_send_msg->direction[i] = _recv_msg->direction;
			_send_msg->posx[i] = _recv_msg->posx;
			_send_msg->posy[i] = _recv_msg->posy;
			_send_msg->current_hp[i] = 10;
			return;
		}
	std::cerr << "Corrupted messsage received (3)" << std::endl;
}