#include <winsock2.h>
#include <ws2tcpip.h>
#include "TCPWinSocket.h"

TCPWinSocket::TCPWinSocket(void)
{
	_fathersocket = INVALID_SOCKET;
}


TCPWinSocket::~TCPWinSocket(void)
{
	if ((closesocket(_fathersocket)) == SOCKET_ERROR)
		std::cerr << "Couldn't close the socket" << std::endl;
}

bool	TCPWinSocket::ConnectToServer(std::string &hostname, std::string port, Selector &sel)
{
	struct timeval    tv;

	//socket creation
	_fathersocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, NULL, WSA_FLAG_OVERLAPPED);
	if (_fathersocket == INVALID_SOCKET)
		return (false);

	tv.tv_sec = 1;
	tv.tv_usec = 0;
	//socket connection
	if ((WSAConnectByName(_fathersocket, hostname.c_str(), port.c_str(), NULL, NULL, NULL, NULL, &tv, NULL)) == FALSE)
		return (false);
	sel.Add_to_checkread(_fathersocket);
	sel.Add_to_checkwrite(_fathersocket);
	return (true);
}

bool				TCPWinSocket::ReadData(CircularBuff &circbuff, Selector &sel)
{
	WSABUF			databuf[3];
	char			first_buff[4];
	char			second_buff[4];
	char			third_buff[256];
	DWORD			recvbytes;
	DWORD			flags = 0;

	databuf[0].len = 4;
	databuf[0].buf = first_buff;
	databuf[1].len = 4;
	databuf[1].buf = second_buff;
	databuf[2].len = 256;
	databuf[2].buf = third_buff;

	if ((sel.Is_readable(_fathersocket)) == true)
	{
		memset(&first_buff, '\0', 4);
		memset(&second_buff, '\0', 4);
		memset(&third_buff, '\0', 256);
		WSARecv(_fathersocket, databuf, 3, &recvbytes, &flags, NULL, NULL);
		if (recvbytes == 0 || (std::string("").compare(databuf[0].buf)) == 0)
		{
			sel.Remove_checkread(_fathersocket);
			sel.Remove_checkwrite(_fathersocket);
			if ((closesocket(_fathersocket)) == SOCKET_ERROR)
				std::cerr << "Couldn't close the socket" << std::endl;
			_fathersocket = INVALID_SOCKET;
			std::cout << "Connection lost with the server" << std::endl;
			return (false);
		}
		Message		Message((uint32_t)*(databuf[0].buf), (uint32_t)*(databuf[1].buf), (void *)databuf[2].buf);

		std::cout << "je recois :"; Message.to_string(); std::cout << std::endl;
		circbuff.add_data(Message);
	}
	return (true);
}

void	TCPWinSocket::SendData(CircularBuff &circbuff, Selector &sel)
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
	for (size_t i = 0; i < to_send->size(); i ++)
		if (sel.Is_writable(_fathersocket))
		{
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

			std::cout << "j'envoi :"; to_send->at(i).to_string(); std::cout << std::endl;
			
			// et on envoi
			WSASend(_fathersocket, databuf, 3, &sentbytes, 0, NULL, NULL);  
		}
	delete to_send;
}
