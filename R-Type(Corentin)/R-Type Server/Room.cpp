#include "Room.h"


Room::Room(std::string &name) :
	_name(name)
{

}


Room::~Room()
{

}


void	Room::Add_Ally(Client &client, CircularBuff &writebuff)
{
	_people.push_back(client);

	//we send to this client all other people in this room
	for (size_t i = 0; i < _people.size() - 1; i++)
	{
		std::string	*allyname = new std::string(_people[i].get_nickname());
		Message		newmess((uint32_t)ADD_ALLY, (uint32_t)(allyname->size()), (void *)(allyname->c_str()), allyname, client);

		writebuff.add_data(newmess);
	}

	//we send to all other people in the room his arrival.
	for (size_t i = 0; i < _people.size() - 1; i++)
	{
		std::string	*allyname = new std::string(client.get_nickname());
		Message		newmess((uint32_t)ADD_ALLY, (uint32_t)(allyname->size()), (void *)(allyname->c_str()), allyname, _people.at(i));

		writebuff.add_data(newmess);
	}
}


void	Room::Remove_Ally(Client &client, CircularBuff &writebuff)
{
	int	ret = NOK;

	for (size_t i = 0; i < _people.size(); i++)
	{
		if (_people[i].get_id() == client.get_id())
		{
			if (_people.size() != 1)
				_people.erase(_people.begin() + i);
			else
				_people.clear();
			ret = OK;
		}
	}
	//on envoi la reponse
	if (ret == OK)
	{
		Message		newmess((uint32_t)ret, (uint32_t)0, (void *)(std::string("").c_str()), NULL, client);
		writebuff.add_data(newmess);
	}
	//si le gars a bien été viré
	if (ret == OK)
	{
		//we send to all other people in the room his leaving
		for (size_t i = 0; i < _people.size(); i++)
		{
			std::string	*allyname = new std::string(client.get_nickname());
			Message		newmess((uint32_t)REMOVE_ALLY, (uint32_t)(allyname->size()), (void *)(allyname->c_str()), allyname, _people.at(i));
			
			writebuff.add_data(newmess);
		}
	}
}

//used for debug purposes
void	Room::To_String() const
{
	std::cout << "Je suis la room : " << _name << std::endl;
	for (size_t i = 0; i < _people.size(); i++)
		std::cout << "ally n * " << i << " : " << _people[i].get_nickname() << std::endl;
}

//getters
std::string		Room::Get_Name() const
{
	return (_name);
}

int				Room::Get_Nb_People() const
{
	return (_people.size());
}

