#pragma once
#include <string>
#include <iostream>
#include <vector>

class Room
{
protected:
	std::string					_name;
	std::vector<std::string>	_allys;

public:
	Room(std::string &name);
	virtual ~Room();

	void	Add_Ally(const std::string &allyname);
	void	Remove_Ally(const std::string &allyname);
	
	const std::string				&get_name() const;
	const std::vector<std::string>	&get_allys() const;

	void	To_String() const;
};

