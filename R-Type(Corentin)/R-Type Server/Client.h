#pragma once
#include <iostream>
#include <string>

#include "Selector.h"

class Client
{
protected:
	std::string		_nickname;
	SOCKET			_socket;
	int				_id;
	std::string		_roomname;

public:
	Client(SOCKET socket, int id, std::string nickname = std::string("DefaultName"), std::string roomname = std::string("DefaultName"));
	//Client();
	virtual ~Client();
	//Client(const Client &other);

	//setters & getters
	std::string				get_nickname(void) const;
	SOCKET					get_socket(void) const;
	int						get_id(void) const;
	std::string				get_room(void) const;

	void			set_nickname(std::string &nickname);
	void			set_id(int id);
	void			set_room(std::string &roomname);
};

