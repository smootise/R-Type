#include "WinThread.h"


WinThread::WinThread(int port) : _port(port)
{

}


WinThread::~WinThread()
{

}

bool	WinThread::start()
{
	_socket = new UDPWinServSocket();
	if (_socket->Connect(_port) == false)
		return (false);
	return (true);
}

bool	WinThread::run()
{
	while (42)
		_socket->Receive_data();
	return (false);
}

void	WinThread::call_run(void *ptr)
{
	WinThread		*T;
	T = reinterpret_cast<WinThread *>(ptr);

	if (T->start() == true)
		T->run();
}