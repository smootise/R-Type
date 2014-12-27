#include "Selector.h"


Selector::Selector(void)
{
	_highestfd = 0;
}


Selector::~Selector(void)
{
	_readtocheck.clear();
	_writetocheck.clear();
}	


void	Selector::Add_to_checkread(SOCKET fd)
{
	_readtocheck.push_back(fd);
	#ifndef _WIN32
		if (fd > _highestfd)	
			_highestfd = fd;
	#endif
}

void	Selector::Add_to_checkwrite(SOCKET fd)
{
	_writetocheck.push_back(fd);
	#ifndef _WIN32
		if (fd > _highestfd)	
			_highestfd = fd;
	#endif
}

void	Selector::Remove_checkread(SOCKET fd)
{
	for (size_t i = 0; i < _readtocheck.size() ; i++)
	{
		if (_readtocheck[i] == fd)
			_readtocheck.erase(_readtocheck.begin() + i);
	}
}

void	Selector::Remove_checkwrite(SOCKET fd)
{
	for (size_t i = 0; i < _writetocheck.size() ; i++)
	{
		if (_writetocheck[i] == fd)
			_writetocheck.erase(_writetocheck.begin() + i);
	}
}

void	Selector::Select(void)
{
	struct timeval	tv;

	FD_ZERO(&_readresult);
	FD_ZERO(&_writeresult);
	for (size_t i = 0; i < _readtocheck.size() ; i++)
		FD_SET(_readtocheck[i], &_readresult);
	for (size_t i = 0; i < _writetocheck.size() ; i++)
		FD_SET(_writetocheck[i], &_writeresult);
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	select(_highestfd + 1, &_readresult, &_writeresult, NULL, &tv);
}


bool	Selector::Is_readable(SOCKET fd)
{
	if ((FD_ISSET(fd, &_readresult)) == 0)
		return (false);
	else
		return (true);
}

bool	Selector::Is_writable(SOCKET fd)
{
	if ((FD_ISSET(fd, &_writeresult)) == 0)
		return (false);
	else
		return (true);
}