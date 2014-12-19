#include <iostream>
#include <sstream>
#include <string>
//#include <SFML/Graphics.hpp>
#include "Client.h"

#ifdef _WIN32
	#pragma comment(lib, "Ws2_32.lib")
#else
	# define EXIT_SUCCESS 0
	# define EXIT_FAILURE -1
#endif

int		main(int ac, char **av)
{ 
	if (ac != 3)
	{
		std::cerr << "Usage : ./client hostname port" << std::endl;
		return (EXIT_FAILURE);
	}

#ifdef _WIN32
	WSADATA				WSAData;
	WSAStartup(MAKEWORD(2,0), &WSAData);
#endif
	bool				continu = true;
	std::string			hostname(av[1]);
	std::string			strport(av[2]);
	Client				client(hostname, strport);

	if (client.init() == false)
	{
		std::cerr << "Couldn't connect to server" << std::endl;
		return (EXIT_FAILURE);
	}

	while (continu == true)
		continu = client.update();
#ifdef _WIN32
	WSACleanup();
#endif
	return (EXIT_SUCCESS);
}
