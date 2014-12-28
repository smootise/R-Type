#include "Room.h"


Room::Room(std::string &name) :
	_name(name), _locked(false)
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
		int			len = _people[i].get_nickname().size();
		char		*allyname = new char[len + 1];
		
		memcpy(allyname, _people[i].get_nickname().c_str(), len + 1);
		Message		newmess(ADD_ALLY, len, allyname, client);

		writebuff.add_data(newmess);
	}

	//we send to all other people in the room his arrival.
	for (size_t i = 0; i < _people.size() - 1; i++)
	{
		int			len = client.get_nickname().size();
		char		*allyname = new char[len + 1];

		memcpy(allyname, client.get_nickname().c_str(), len + 1);
		Message		newmess(ADD_ALLY, len, allyname, _people.at(i));

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
		Message		newmess(ret, 0, NULL, client);
		writebuff.add_data(newmess);
	}
	//si le gars a bien été viré
	if (ret == OK)
	{
		//we send to all other people in the room his leaving
		for (size_t i = 0; i < _people.size(); i++)
		{
			int			len = client.get_nickname().size();
			char		*allyname = new char[len + 1];

			memcpy(allyname, client.get_nickname().c_str(), len + 1);
			Message		newmess(REMOVE_ALLY, len, allyname, _people.at(i));
			
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
const std::string		&Room::Get_Name() const
{
	return (_name);
}

int				Room::Get_Nb_People() const
{
	return (_people.size());
}

std::vector<Client>		&Room::get_people()
{
	return (_people);
}

bool				Room::is_locked() const
{
	return (_locked);
}

void				Room::set_locked(bool val)
{
	_locked = val;
}