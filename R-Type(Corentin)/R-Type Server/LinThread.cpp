#include "LinThread.h"


LinThread::LinThread(int port) : _port(port)
{

}


LinThread::~LinThread()
{

}

bool	LinThread::start()
{
  _socket = new UDPLinServSocket();
  if (_socket->Connect(_port) == false)
    return (false);
  return (true);
}

bool	LinThread::run()
{
  while (42)
    _socket->Receive_data();
  return (false);
}

void	 *LinThread::call_run(void *ptr)
{
  LinThread		*T;
  T = reinterpret_cast<LinThread *>(ptr);

  if (T->start() == true)
    T->run();
}
