#pragma once
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

public:
	Room(std::string &name);
	virtual ~Room();

	void	Add_Ally(Client &client, CircularBuff &_writebuff);
	void	Remove_Ally(Client &client, CircularBuff &_writebuff);
	void	To_String() const;

	//getters
	std::string		Get_Name() const;
	int				Get_Nb_People() const;
};

