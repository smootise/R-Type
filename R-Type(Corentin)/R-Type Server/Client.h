#pragma once
#include <iostream>
#include <string>

#include "Selector.h"


// a modifier
enum
{
	UNKNOWN,
	KNOWN,
	DISCONNECTED,
	CONNECTED,
};

class Client
{
protected:
	std::string		_nickname;
	SOCKET			_socket;
	int				_id;
	int				_state; //reserved for further user
	int				_room;

public:
	Client(SOCKET socket, int id, int state = UNKNOWN, std::string nickname  = std::string("DefaultName"), int room = -1);
	virtual ~Client();

	//setters & getters
	std::string		&get_nickname(void);
	SOCKET			get_socket(void);
	int				get_id(void);
	int				get_state(void);
	int				get_room(void);

	void			set_nickname(std::string &nickname);
	void			set_id(int id);
	void			set_state(int state);
	void			set_room(int room);
};

