#include "TCPLinServSocket.h"

TCPLinServSocket::TCPLinServSocket(std::vector<Client> &client) :
_clients(client)
{
	_fathersocket = INVALID_SOCKET;
}

TCPLinServSocket::~TCPLinServSocket(void)
{
	//clean all the sockets
	if (_fathersocket != INVALID_SOCKET)
		close(_fathersocket);
	for (size_t i = 0; i < _clients.size(); i++)
		close(_clients[i].get_socket());
}

bool			TCPLinServSocket::Connect(int port, Selector &sel)
{
	struct sockaddr_in    s_in;
	struct protoent	*pe;

	if ((pe = getprotobyname("TCP")) == NULL)
		return (false);
	// Socket creation
	if ((_fathersocket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == INVALID_SOCKET)
		return (false);
	//Socket binding
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;

	if ((bind(_fathersocket, (const struct sockaddr *)&s_in, sizeof(s_in))) == INVALID_SOCKET)
		return (false);

	//Socket listening
	if ((listen(_fathersocket, 42)) == INVALID_SOCKET)
		return (false);
	//Add to selector for monitoring
	sel.Add_to_checkread(_fathersocket);
	return (true);
}

bool			TCPLinServSocket::SearchNewClients(Selector &sel)
{
	SOCKET		newclientsocket;
	int			highestid = 1;
	struct sockaddr_in	s_in;
	socklen_t		s_size;

	s_size = sizeof(s_in);
	if ((sel.Is_readable(_fathersocket)) == true)
	{
		if ((newclientsocket = accept(_fathersocket, (struct sockaddr *)&s_in, &s_size)) == INVALID_SOCKET)
		{
			std::cerr << "Couldn't accept a new client" << std::endl;
			return (false);
		}
		sel.Add_to_checkread(newclientsocket);
		sel.Add_to_checkwrite(newclientsocket);
		for (size_t i = 0; i < _clients.size(); i++)
		if (_clients[i].get_id() >= highestid)
			highestid = _clients[i].get_id() + 1;

		Client	newclient(newclientsocket, highestid);
		_clients.push_back(newclient);
	}
	return (true);
}

void				TCPLinServSocket::ReadData(CircularBuff &circbuff, Selector &sel)
{
  struct iovec		databuf[3];
  char				first_buff[4];
  char				second_buff[4];
  char				third_buff[256];
  int				recvbytes = 0;

  databuf[0].iov_len = 4;
  databuf[0].iov_base = first_buff;
  databuf[1].iov_len = 4;
  databuf[1].iov_base = second_buff;
  databuf[2].iov_len = 256;
  databuf[2].iov_base = third_buff;

  // pour toutes les sockets
  for (size_t i = 0; i < _clients.size(); i++)
    // si il y a de la data a lire
    if ((sel.Is_readable(_clients[i].get_socket())) == true)
      {
		//on reset les bails
		memset(&first_buff, '\0', 4);
		memset(&second_buff, '\0', 4);
		memset(&third_buff, '\0', 256);
		recvbytes = readv(_clients[i].get_socket(), databuf, 3);
		if (recvbytes == 0 || (std::string("").compare((char *)databuf[0].iov_base)) == 0)
		  {
			sel.Remove_checkread(_clients[i].get_socket());
			sel.Remove_checkwrite(_clients[i].get_socket());
			if (_clients.size() != 1)
			  _clients.erase(_clients.begin() + i);
			else
			  _clients.clear();
		  }
		else
		  {
			int				len = strlen((char *)databuf[2].iov_base);
			char			*packet = new char[len + 1];

			memcpy(packet, databuf[2].iov_base, len + 1);
			Message			message((uint32_t)*((char *)(databuf[0].iov_base)), (uint32_t)*((char *)(databuf[1].iov_base)), packet, _clients[i]);

			circbuff.add_data(message);
		  }
      }
}

// ICI l'id du client correspond a l'id du client auquel on veut envoyer les bails
void		TCPLinServSocket::SendData(CircularBuff &circbuff, Selector &sel)
{
	std::vector<Message>		&to_send = circbuff.get_data();
	struct iovec				databuf[3];
	char						first_buff[4];
	char						second_buff[4];
	char						third_buff[256];
	int							sentbytes = 0;
		
	databuf[0].iov_len = 4;
	databuf[0].iov_base = first_buff;
	databuf[1].iov_len = 4;
	databuf[1].iov_base = second_buff;
	databuf[2].iov_len = 256;
	databuf[2].iov_base = third_buff;

	//pour tous les messages
	for (size_t i = 0; i < to_send.size(); i++)
		if (sel.Is_writable(to_send.at(i).get_client().get_socket()))
		{
			//reset des buffers
			memset(&first_buff, '\0', 4);
			memset(&second_buff, '\0', 4);
			memset(&third_buff, '\0', 256);

			// on crée des variables parce qu'on a besoin d'une
			//adresse pour memcpy (donc juste des getters ca suffit pas)
			int		rq_type = to_send.at(i).get_rq_type();
			int		data_length = to_send.at(i).get_data_length();

			//on rempli nos 3 buffers
			memcpy(&first_buff, (char *)&(rq_type), 4);
			memcpy(&second_buff, (char *)&(data_length), 4);
			memcpy(&third_buff, to_send.at(i).get_packet(), data_length);

			// et on les envoi
			sentbytes = writev(to_send.at(i).get_client().get_socket(), databuf, 3);
			delete[]	to_send.at(i).get_packet();
		}
	to_send.clear();
}
