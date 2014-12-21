#include "WinThread.h"


WinThread::WinThread(int port) : _port(port)
{

}


WinThread::~WinThread()
{

}

void	WinThread::start()
{

}

bool	WinThread::run()
{
	int			i;

	i = 0;
	while (i < 100)
	{
		std::cout << "je run ! : " << _port << std::endl;
		i++;
	}
		return (false);
}

void	WinThread::call_run(void *ptr)
{
	WinThread		*T;
	T = reinterpret_cast<WinThread *>(ptr);

	T->start();
	T->run();
}