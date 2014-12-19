#include "Room.h"


Room::Room(std::string &name)
	:_name(name)
{

}

Room::~Room()
{
}

void	Room::Add_Ally(const std::string &allyname)
{
	_allys.push_back(allyname);
}


void	Room::Remove_Ally(const std::string &allyname)
{
	for (size_t i = 0; i < _allys.size(); i++)
	{
		if (_allys.at(i) == allyname)
		{
			if (_allys.size() != 1)
				_allys.erase(_allys.begin() + i);
			else
				_allys.clear();
		}
	}
}

//used for debug purposes
void	Room::To_String() const
{
	std::cout << "Je suis la room : " << _name << std::endl;
	for (size_t i = 0; i < _allys.size(); i++)
		std::cout << "ally n * " << i << " : " << _allys.at(i) << std::endl;
}

const std::string		&Room::get_name() const
{
	return (_name);
}

const std::vector<std::string>	&Room::get_allys() const
{
	return (_allys);
}
