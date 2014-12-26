#pragma once
#include <iostream>
#include <vector>

#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
#else
	typedef int SOCKET;
	#include <sys/select.h>
#endif

class Selector
{
protected:
	std::vector<SOCKET>		_readtocheck;
	std::vector<SOCKET>		_writetocheck;
	fd_set					_readresult;
	fd_set					_writeresult;
	int						_highestfd;
	 
public:
	Selector(void);
	virtual ~Selector(void);

void	Add_to_checkread(SOCKET fd);
void	Add_to_checkwrite(SOCKET fd);
void	Remove_checkread(SOCKET fd);
void	Remove_checkwrite(SOCKET fd);
void	Select(void);
bool	Is_readable(SOCKET fd);
bool	Is_writable(SOCKET fd);
};
