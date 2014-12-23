#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/uio.h>
#include <cstdlib>
#include <unistd.h> // requis pour gethostbyname
#include <stdlib.h>
#include <string.h> //requis pour memset
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sstream>
#include <fcntl.h>

#include "IUDPSocket.h"

class UDPLinSocket : public IUDPSocket
{
 protected:
  struct sockaddr_in		_server;
  int					_socket;
  std::string			_ipsource;
  bool					_connected;

 public:
  UDPLinSocket(std::string &ipsource);
  virtual ~UDPLinSocket();

  virtual bool	Connect(int port);
  virtual bool	Send_data(ClientMessage *);
  virtual bool	Receive_data(ServerMessage *recv_msg);
  virtual bool	is_connected();
};

