#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Server.h"

#ifdef _WIN32
	#pragma comment(lib, "Ws2_32.lib")
#endif

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage : ./server port" << std::endl;
		return (EXIT_FAILURE);
	}
	std::string			*strport = new std::string(av[1]);
	int					intport;

	intport = atoi(strport->c_str());

	#ifdef _WIN32
		WSADATA				WSAData;
		WSAStartup(MAKEWORD(2,0), &WSAData);
	#endif
	Server				serv(intport);
	bool				continu = true;

	if (serv.init() == false)
	{
		std::cerr << "Couldn't init socket utilisation" << std::endl;
		return (EXIT_FAILURE);
	}

	while (continu == true)
		continu = serv.update();
	#ifdef _WIN32
		WSACleanup();
	#endif
	return (EXIT_SUCCESS);
}
