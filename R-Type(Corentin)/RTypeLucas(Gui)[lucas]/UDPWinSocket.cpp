#include "UDPWinSocket.h"


UDPWinSocket::UDPWinSocket(std::string &ipsource) : _ipsource(ipsource)
{
	_socket = INVALID_SOCKET;
	_connected = false;
}


UDPWinSocket::~UDPWinSocket()
{
	if (_socket != INVALID_SOCKET)
		closesocket(_socket);
}

bool	UDPWinSocket::Connect(int port)
{
	u_short				rethtons;
	char				host_name[256];
	struct hostent		*hp;
	std::vector<int>	separated_ip(4, 0);
	size_t				dot_pos;
	int					i = 0;
	int					pos_start = 0;
	int					pos_end = 0;

	dot_pos = -1;
	// on decoupe l'ip en 4 int !
	while ((dot_pos = _ipsource.find(".", dot_pos + 1)) != std::string::npos)
	{
		if (i > 3)
		{
			std::cerr << "invalid ip address : only ipv4 is supported by this prog" << std::endl;
			return (false);
		}
		pos_end = dot_pos;
		separated_ip[i] = atoi(_ipsource.substr(pos_start, pos_end - pos_start).c_str());
		pos_start = pos_end + 1;
		i++;
	}
	separated_ip[3] = atoi(_ipsource.substr(pos_start).c_str());
	std::cout << "ip : " << separated_ip[0] << "." << separated_ip[1] << "." << separated_ip[2] << "." << separated_ip[3] << std::endl;

	/* Open a datagram socket */
	if ((_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, NULL, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		std::cerr << "couldn't create the socket" << std::endl;
		return (false);
	}
	/* Clear out server struct */
	memset((void *)&_server, '\0', sizeof(struct sockaddr_in));
	/* Set family and port */
	_server.sin_family = AF_INET;
	WSAHtons(_socket, port, &rethtons);
	_server.sin_port = rethtons;
	/* Set server address */
	_server.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)(separated_ip.at(0));
	_server.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)(separated_ip.at(1));
	_server.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)(separated_ip.at(2));
	_server.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)(separated_ip.at(3));

	/* Clear out client struct */
	memset((void *)&_client, '\0', sizeof(struct sockaddr_in));
	/* Set family and port */
	_client.sin_family = AF_INET;
	WSAHtons(_socket, 0, &rethtons);
	_client.sin_port = rethtons;


	/* Get host name of this computer */
	gethostname(host_name, sizeof(host_name));
	if ((hp = gethostbyname(host_name)) == NULL)
	{
		std::cerr << "Couldn't get hostname" << std::endl;
		return (false);
	}
	/* Assign the address */
	_client.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
	_client.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
	_client.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
	_client.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];

	/* Bind local address to socket */
	if (bind(_socket, (struct sockaddr *)&_client, sizeof(struct sockaddr_in)) == -1)
	{
		std::cerr << "could'nt bind the socket" << std::endl;
		return (false);
	}

	// set socket to non-blocking
	unsigned long			mode = 1;
	if ((ioctlsocket(_socket, FIONBIO, &mode)) == SOCKET_ERROR)
	{
		std::cerr << "couldn't set socket to non bloking mode " << std::endl;
		return (false);
	}
	_connected = true;
	return (true);
} 

bool	UDPWinSocket::Send_data()
{
	DWORD				send_flags = 0;
	DWORD				sent_bytes = 0;
	WSABUF				sendbuff[1];
	char				buff[8192];
	int					server_length;

	sendbuff[0].len = 8192;
	sendbuff[0].buf = buff;
	server_length = (int)sizeof(struct sockaddr_in);

	//on memset le buff
	memset(buff, '\0', 8192);
	//on copie les bails
	memcpy(&buff, std::string("test").c_str(), 4);
	if ((WSASendTo(_socket, sendbuff, 1, &sent_bytes, send_flags, (struct sockaddr *)&_server, server_length, NULL, NULL)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return (true);
		else
		{
			std::cerr << "coudldn't use send to" << std::endl;
			return (true);
		}
	}
	return (true);
}

bool	UDPWinSocket::Receive_data()
{
	DWORD				recv_flags = 0;
	DWORD				recv_bytes = 0;
	WSABUF				recvbuff[1];
	char				buff[8192];
	int					server_length;

	recvbuff[0].len = 8192;
	recvbuff[0].buf = buff;
	server_length = (int)sizeof(struct sockaddr_in);

	memset(buff, '\0', 8192);

	/* Receive bytes from client */
	std::cout << "avant recv from" << std::endl;
	if ((WSARecvFrom(_socket, recvbuff, 1, &recv_bytes, &recv_flags, (struct sockaddr *)&_server, &server_length, NULL, NULL)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return (true);
		else
		{
			std::cerr << "couldn't recv from" << std::endl;
			return (true);
		}
	}
	std::cout << "j'ai recu : " << recvbuff[0].buf << std::endl;
	return (true);
}

bool	UDPWinSocket::is_connected()
{
	return (_connected);
}