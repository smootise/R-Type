#include "TCPWinServSocket.h"

TCPWinServSocket::TCPWinServSocket(std::vector<Client> &client)
	: _clients(client)
{

}


TCPWinServSocket::~TCPWinServSocket()
{
	//clean all the sockets
	closesocket(_fathersocket);
	for (size_t i = 0; i < _clients.size(); i++)
		closesocket(_clients[i].get_socket());
}

bool		TCPWinServSocket::Connect(int port, Selector &sel)
{
	struct sockaddr_in    s_in;
	u_short				  ret;

	// Socket creation
	_fathersocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, NULL, WSA_FLAG_OVERLAPPED);
	if (_fathersocket == INVALID_SOCKET)
		return (false);
	//Socket binding
	s_in.sin_family = AF_INET;
	s_in.sin_addr.s_addr = INADDR_ANY;
	if ((WSAHtons(_fathersocket, port, &ret)) == SOCKET_ERROR)
		return (false);
	
	s_in.sin_port = ret;
	if ((bind(_fathersocket, (const struct sockaddr *)&s_in, sizeof(s_in))) == SOCKET_ERROR)
		return (false);

	//Socket listening
	if ((listen(_fathersocket, SOMAXCONN)) == SOCKET_ERROR)
		return (false);
	//Add to selector for monitoring
	sel.Add_to_checkread(_fathersocket);
	return (true);
}

bool		TCPWinServSocket::SearchNewClients(Selector &sel)
{
	SOCKET	newclientsocket;
	int		highestid = 1;

	if ((sel.Is_readable(_fathersocket)) == true)
	{
		if ((newclientsocket = WSAAccept(_fathersocket, NULL, NULL, NULL, NULL)) == INVALID_SOCKET)
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

void				TCPWinServSocket::ReadData(CircularBuff &circbuff, Selector &sel)
{
	DWORD			recvbytes;
	WSABUF			databuf[3];
	DWORD			flags = 0;
	char			first_buff[4];
	char			second_buff[4];
	char			third_buff[256];

	databuf[0].len = 4;
	databuf[0].buf = first_buff;
	databuf[1].len = 4;
	databuf[1].buf = second_buff;
	databuf[2].len = 256;
	databuf[2].buf = third_buff;

	// pour toutes les sockets
	for (size_t i = 0; i < _clients.size(); i++)
		// si il y a de la data a lire
		if ((sel.Is_readable(_clients[i].get_socket())) == true)
		{
			//on reset les bails
			memset(&first_buff, '\0', 4);
			memset(&second_buff, '\0', 4);
			memset(&third_buff, '\0', 256);
			WSARecv(_clients[i].get_socket(), databuf, 3, &recvbytes, &flags, NULL, NULL);
			if (recvbytes == 0 || (std::string("").compare(databuf[0].buf)) == 0)
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
				std::string		*str = new std::string(databuf[2].buf);
				Message		message((uint32_t)*(databuf[0].buf), (uint32_t)*(databuf[1].buf), (void *)(str->c_str()), str, _clients[i]);

				std::cout << "je recois :"; message.to_string(); std::cout << std::endl;
				circbuff.add_data(message);
			}
		}
}

// ICI l'id du client correspond a l'id du client auquel on veut envoyer les bails
void		TCPWinServSocket::SendData(CircularBuff &circbuff, Selector &sel)
{
	std::vector<Message>		*to_send;
	DWORD						sentbytes;
	WSABUF						databuf[3];
	char						first_buff[4];
	char						second_buff[4];
	char						third_buff[256];

	databuf[0].len = 4;
	databuf[0].buf = first_buff;
	databuf[1].len = 4;
	databuf[1].buf = second_buff;
	databuf[2].len = 256;
	databuf[2].buf = third_buff;

	to_send = circbuff.get_data();
	//pour tous les messages
	for (size_t i = 0; i < to_send->size(); i++)
	if (sel.Is_writable(to_send->at(i).get_client().get_socket()))
	{
		//reset des buffers
		memset(&first_buff, '\0', 4);
		memset(&second_buff, '\0', 4);
		memset(&third_buff, '\0', 256);

		// on crée des variables parce qu'on a besoin d'une adresse pour memcpy (donc juste des getters ca suffit pas)
		int		rq_type = to_send->at(i).get_rq_type();
		int		data_length = to_send->at(i).get_data_length();

		//on rempli nos 3 buffers
		memcpy(&first_buff, (char *)&(rq_type), 4);
		memcpy(&second_buff, (char *)&(data_length), 4);
		memcpy(&third_buff, (char *)(to_send->at(i).get_packet()), data_length);

		// et on les envoi
		std::cout << "j'envois :"; to_send->at(i).to_string(); std::cout << std::endl;
		WSASend(to_send->at(i).get_client().get_socket(), databuf, 3, &sentbytes, 0, NULL, NULL);
	}
	else
		std::cerr << "Corruption possible (1)" << std::endl;
	delete to_send;
}