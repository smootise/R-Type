#include "UDPLinSocket.h"


UDPLinSocket::UDPLinSocket(std::string &ipsource) : _ipsource(ipsource)
{
  _socket = -1;
  _connected = false;
}


UDPLinSocket::~UDPLinSocket()
{
  if (_socket != -1)
    close(_socket);
}

bool	UDPLinSocket::Connect(int port)
{
  int					i = 0;
  struct protoent			*pe;

  std::cout << "ip : " << _ipsource << std::endl;

  /* get protocol informations */
  if ((pe = getprotobyname("UDP")) == NULL)
    return (false);
  /* Open a datagram socket */
  if ((_socket = socket(AF_INET, SOCK_DGRAM, pe->p_proto)) == -1)
    {
      std::cerr << "couldn't create the socket" << std::endl;
      return (false);
    }
  /* Clear out server struct */
  memset((void *)&_server, '\0', sizeof(struct sockaddr_in));
  /* Set family and port */
  _server.sin_family = AF_INET;
  _server.sin_port = htons(port);

  /* Set server address */
  inet_aton(_ipsource.c_str(), &_server.sin_addr);

  // Set socket to non-bloking mode
  int				non_blocking = 1;
  if (fcntl( _socket, F_SETFL, O_NONBLOCK, non_blocking ) == -1 )
    {
      std::cerr << "failed to set non-blocking socket" << std::endl;
      return false;
    }
  _connected = true;
  return (true);
} 

bool	UDPLinSocket::Send_data(ClientMessage *send_msg)
{
  int		send_flags = 0;
  int		sent_bytes = 0;
  char		buff[8192];
  int		server_length;

  server_length = (int)sizeof(struct sockaddr_in);

  //on memset le buff
  memset(buff, '\0', 8192);
  //on copie les bails
  memcpy(&buff, (void *)send_msg, sizeof(ClientMessage));
  if ((sent_bytes = sendto(_socket, buff, 8192, send_flags,
			   (struct sockaddr *)&_server, server_length)) == 0)
    {
      std::cerr << "coudldn't use send to" << std::endl;
      return (false);
    }
  return (true);
}

bool	UDPLinSocket::Receive_data(ServerMessage *recv_msg)
{
  int				recv_flags = 0;
  int				recv_bytes = 0;
  char				buff[8192];
  socklen_t			server_length;

  server_length = (int)sizeof(struct sockaddr_in);
  memset(buff, '\0', 8192);
  /* Receive bytes from client */
  if ((recv_bytes = recvfrom(_socket, buff, 8192, recv_flags,
			     (struct sockaddr *)&_server, &server_length)) == 0)
    {
      //std::cerr << "couldn't recv from" << std::endl;
      return (false);
    }
  if (recv_bytes != -1)
    {
      memcpy(recv_msg, (void *)buff, sizeof(ServerMessage));
    }
  return (true);
}

bool	UDPLinSocket::is_connected()
{
	return (_connected);
}
