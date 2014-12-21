#include "LinThread.h"


LinThread::LinThread(int port) : _port(port)
{

}


LinThread::~LinThread()
{

}

void	LinThread::start()
{

}

bool	LinThread::run()
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

void	LinThread::call_run(void *ptr)
{
	LinThread		*T;
	T = reinterpret_cast<LinThread *>(ptr);

	T->start();
	T->run();
}