#include "UDPWinServSocket.h"


UDPWinServSocket::UDPWinServSocket()
{
	_socket = INVALID_SOCKET;
}


UDPWinServSocket::~UDPWinServSocket()
{
	if (_socket != INVALID_SOCKET)
		closesocket(_socket);
}

bool			UDPWinServSocket::Connect(int port)
{
	u_short				rethtons;

	/* Open a datagram socket */
	if ((_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, NULL, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		std::cerr << "couldn't create the socket" << std::endl;
		return (false);
	}
	/* Clear out server struct */
	memset((void *)&_serv, '\0', sizeof(struct sockaddr_in));

	/* Set family and port */
	_serv.sin_family = AF_INET;
	WSAHtons(_socket, port, &rethtons);
	_serv.sin_port = rethtons;
	_serv.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Bind address to socket */
	if (bind(_socket, (struct sockaddr *)&_serv, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		std::cerr << "couldn't bind the socket" << std::endl;
		return (false);
	}

	// set socket to non-blocking
	unsigned long			mode = 1;
	if ((ioctlsocket(_socket, FIONBIO, &mode)) == SOCKET_ERROR)
	{
		std::cerr << "couldn't set socket to non bloking mode " << std::endl;
		return (false);
	}
	return (true);
}

bool			UDPWinServSocket::Receive_data(ClientMessage *recv_msg, ServerMessage *send_msg)
{
	DWORD				recv_flags = 0;
	DWORD				recv_bytes = 0;
	WSABUF				recvbuff[1];
	char				buff[8192];
	struct sockaddr_in	client;
	int					client_length;

	recvbuff[0].len = 8192;
	recvbuff[0].buf = buff;
	client_length = (int)sizeof(struct sockaddr_in);

	memset(buff, '\0', 8192);

	/* Receive bytes from client */ 
	if ((WSARecvFrom(_socket, recvbuff, 1, &recv_bytes, &recv_flags, (struct sockaddr *)&client, &client_length, NULL, NULL)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return (true);
		else
		{
			std::cerr << "couldn't recv from" << std::endl;
			return (true);
		}
	}
	memcpy(recv_msg, (void *)buff, sizeof(ClientMessage));
	recv_msg->has_been_read = false;
	return (this->send_data(&client, send_msg));
}

bool			UDPWinServSocket::send_data(struct sockaddr_in *target, ServerMessage *send_msg)
{
	DWORD				send_flags = 0;
	DWORD				sent_bytes = 0;
	WSABUF				sendbuff[1];
	char				buff[8192];
	int					client_length;

	sendbuff[0].len = 8192;
	sendbuff[0].buf = buff;
	client_length = (int)sizeof(struct sockaddr_in);

	memset(buff, '\0', 8192);
	//on copie les bails
	memcpy(&buff, send_msg, sizeof(ServerMessage));
	if ((WSASendTo(_socket, sendbuff, 1, &sent_bytes, send_flags, (struct sockaddr *)target, client_length, NULL, NULL)) == SOCKET_ERROR)
	{
		//std::cerr << "coudldn't use send to" << std::endl;
		return (true);
	}
	return (true);
}