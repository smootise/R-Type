#include "LinThread.h"


LinThread::LinThread(int port) : _port(port)
{

}


LinThread::~LinThread()
{

}

bool		LinThread::start()
{
  std::string	name_default("DefaultName");

  _socket = new UDPLinServSocket();
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

bool	LinThread::run()
{
  while (42)
    {
      _socket->Receive_data(_recv_msg, _send_msg);
      this->analyse_data();
    }
  return (false);
}

void	 *LinThread::call_run(void *ptr)
{
  LinThread		*T;
  T = reinterpret_cast<LinThread *>(ptr);

  if (T->start() == true)
    T->run();
}

void			LinThread::analyse_data()
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
	return;
      }
  std::cerr << "Corrupted messsage received (3)" << std::endl;
}
