#include "UDPLinServSocket.h"


UDPLinServSocket::UDPLinServSocket()
{
  _socket = -1;
}


UDPLinServSocket::~UDPLinServSocket()
{
  if (_socket != -1)
    close(_socket);
}

bool			UDPLinServSocket::Connect(int port)
{
  struct protoent			*pe;

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
  memset((void *)&_serv, '\0', sizeof(struct sockaddr_in));

  /* Set family and port */
  _serv.sin_family = AF_INET;
  _serv.sin_port = htons(port);
  _serv.sin_addr.s_addr = htonl(INADDR_ANY);

  /* Bind address to socket */
  if (bind(_socket, (struct sockaddr *)&_serv, sizeof(struct sockaddr_in)) == -1)
    {
      std::cerr << "couldn't bind the socket" << std::endl;
      return (false);
    }
  // Set socket to non-bloking mode
  int				non_blocking = 1;
  if (fcntl( _socket, F_SETFL, O_NONBLOCK, non_blocking ) == -1 )
    {
      std::cerr << "failed to set non-blocking socket" << std::endl;
      return false;
    }

  return (true);
}

bool			UDPLinServSocket::Receive_data()
{
  int				recv_flags = 0;
  int				recv_bytes = 0;
  char				buff[8192];
  struct sockaddr_in		client;
  socklen_t		       	client_length;

  client_length = (int)sizeof(struct sockaddr_in);

  memset(buff, '\0', 8192);
  /* Receive bytes from client */
  if ((recv_bytes = recvfrom(_socket, buff, 8192, recv_flags,
			     (struct sockaddr *)&client, &client_length)) == 0)
    {
      std::cerr << "couldn't recv from" << std::endl;
      return (false);
    }
  if (recv_bytes != -1)
    {
      std::cout << "j'ai recu : " << buff << std::endl;
      return (this->send_data(&client));
    }
  return (true);
}

bool			UDPLinServSocket::send_data(struct sockaddr_in *target)
{
  int				send_flags = 0;
  int				sent_bytes = 0;
  char				buff[8192];
  int				client_length;

  client_length = (int)sizeof(struct sockaddr_in);

  memset(buff, '\0', 8192);
  //on copie les bails
  memcpy(&buff, std::string("test").c_str(), 4);
  if ((sent_bytes = sendto(_socket, buff, 8192, send_flags,
			   (struct sockaddr *)target, client_length)) == 0)
    {
      std::cerr << "coudldn't use send to" << std::endl;
      return (false);
    }
  std::cout << " j'ai renvoyé " << buff << std::endl;
  return (true);
}
