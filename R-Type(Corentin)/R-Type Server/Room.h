#pragma once
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include "Client.h"
#include "CircularBuff.h"
#include "Message.h"
#include "Commands.h"

class Room
{
protected:
	std::string					_name;
	std::vector<Client>			_people;
	bool						_locked;

public:
	Room(std::string &name);
	virtual ~Room();

	void	Add_Ally(Client &client, CircularBuff &_writebuff);
	void	Remove_Ally(Client &client, CircularBuff &_writebuff);
	void	To_String() const;

	std::vector<Client>		&get_people();
	//getters
	const std::string		&Get_Name() const;
	int						Get_Nb_People() const;

	bool				is_locked() const;
	void				set_locked(bool val);
};

