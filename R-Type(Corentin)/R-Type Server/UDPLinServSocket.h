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
#include <string.h> //requis pour memset
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sstream>
#include <fcntl.h>

#include "IUDPServSocket.h"

class UDPLinServSocket :  public IUDPServSocket
{
 protected:
  struct sockaddr_in		_serv;
  int				_socket;

 public:
  UDPLinServSocket();
  virtual ~UDPLinServSocket();

  virtual bool	Connect(int port);
  virtual bool	Receive_data();
 protected:
  virtual bool	send_data(struct sockaddr_in *target);
};

