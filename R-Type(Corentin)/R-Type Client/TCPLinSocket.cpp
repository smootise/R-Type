#include "TCPLinSocket.h"


TCPLinSocket::TCPLinSocket(void)
{
	_fathersocket = INVALID_SOCKET;
}


TCPLinSocket::~TCPLinSocket(void)
{
	if ((close(_fathersocket)) == -1)
		std::cerr << "Couldn't close the socket" << std::endl;
}

bool			TCPLinSocket::ConnectToServer(std::string &hostname, std::string port,
	Selector &sel)
{
	struct protoent	*pe;
	struct sockaddr_in    s_in;

	//socket creation
	if ((pe = getprotobyname("TCP")) == NULL)
		return (false);
	if ((_fathersocket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		return (false);

	//socket connection
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(atoi(port.c_str()));
	s_in.sin_addr.s_addr = inet_addr(hostname.c_str());

	if ((connect(_fathersocket, (struct sockaddr *)&s_in, sizeof(s_in))) == -1)
		return (false);

	sel.Add_to_checkread(_fathersocket);
	sel.Add_to_checkwrite(_fathersocket);
	return (true);
}

bool		TCPLinSocket::ReadData(CircularBuff &circbuff, Selector &sel)
{
	struct iovec	databuf[3];
	char		first_buff[4];
	char		second_buff[4];
	char		third_buff[256];
	int		recvbytes = 0;

	databuf[0].iov_len = 4;
	databuf[0].iov_base = first_buff;
	databuf[1].iov_len = 4;
	databuf[1].iov_base = second_buff;
	databuf[2].iov_len = 256;
	databuf[2].iov_base = third_buff;

	if ((sel.Is_readable(_fathersocket)) == true)
	{
		memset(&first_buff, '\0', 4);
		memset(&second_buff, '\0', 4);
		memset(&third_buff, '\0', 256);
		recvbytes = readv(_fathersocket, databuf, 3);
		if (recvbytes == 0 || (std::string("").compare((char *)databuf[0].iov_base)) == 0)
		{
			sel.Remove_checkread(_fathersocket);
			sel.Remove_checkwrite(_fathersocket);
			if ((close(_fathersocket)) == -1)
				std::cerr << "Couldn't close the socket" << std::endl;
			_fathersocket = INVALID_SOCKET;
			std::cout << "Connection lost with the server" << std::endl;
			return (false);
		}
		Message		Message((uint32_t)*((char *)(databuf[0].iov_base)),
			(uint32_t)*((char *)(databuf[1].iov_base)),
			(void *)databuf[2].iov_base);
		circbuff.add_data(Message);
	}
	return (true);
}

void				TCPLinSocket::SendData(CircularBuff &circbuff, Selector &sel)
{
	std::vector<Message>		*to_send;
	struct iovec			databuf[3];
	char				first_buff[4];
	char				second_buff[4];
	char				third_buff[256];
	int				sentbytes = 0;

	databuf[0].iov_len = 4;
	databuf[0].iov_base = first_buff;
	databuf[1].iov_len = 4;
	databuf[1].iov_base = second_buff;
	databuf[2].iov_len = 256;
	databuf[2].iov_base = third_buff;

	to_send = circbuff.get_data();
	for (size_t i = 0; i < to_send->size(); i++)
	if (sel.Is_writable(_fathersocket))
	{
		memset(&first_buff, '\0', 4);
		memset(&second_buff, '\0', 4);
		memset(&third_buff, '\0', 256);

		// on crée des variables parce qu'on a besoin d'une
		//adresse pour memcpy (donc juste des getters ca suffit pas)
		int		rq_type = to_send->at(i).get_rq_type();
		int		data_length = to_send->at(i).get_data_length();

		//on rempli nos 3 buffers
		memcpy(&first_buff, (char *)&(rq_type), 4);
		memcpy(&second_buff, (char *)&(data_length), 4);
		memcpy(&third_buff, (char *)(to_send->at(i).get_packet()), data_length);

		std::cout << "j'envoi :"; to_send->at(i).to_string(); std::cout << std::endl;
		// et on envoi
		sentbytes = writev(_fathersocket, databuf, 3);
	}
	delete to_send;
}
