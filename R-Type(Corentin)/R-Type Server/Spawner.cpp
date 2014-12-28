#include "Spawner.h"
#include "AMonster.h"

#ifdef _WIN32
	#include "WinDllLoader.h"
#else
	#include "LinDllLoader.h"
#endif


Spawner::Spawner() : _level(1), _over(false)
{
	_monster_creation["light"] = &Spawner::CreateLight;
	_monster_creation["medium"] = &Spawner::CreateMedium;
	_monster_creation["heavy"] = &Spawner::CreateHeavy;
	_monster_creation["boss"] = &Spawner::CreateBoss;

#ifdef _WIN32
	_LibLoader = new WinDllLoader();
#else
	_LibLoader = new LinDllLoader();
#endif

	_LibLoader->loadfromfile("Libs/Librairies.txt");
	_lowestmobid = 1;
	_lowestshotid = 1;
}

Spawner::~Spawner()
{

}

bool Spawner::LoadMonsters(const char *fileName)
{
	int				line_nbr;
	std::string		line;
	std::string		timing;
	std::string		type;
	std::ifstream	myfile(fileName);

	line_nbr = 1;
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			if (line.empty() == false && line[0] != '#')
			{
				timing = line.substr(line.find_first_of(":") + 1, 5);
				type = line.substr(0, line.find_first_of(":"));

				if (_monster_creation.count(type) > 0)
					(this->*_monster_creation[type])(timing.c_str());
				else
				{
					std::cerr << "Error reading lvlfile : line " << line_nbr << " is corrupted." << std::endl;
					return (false);
				}
			}
			line_nbr = line_nbr + 1;
		}
		myfile.close();
		return (true);
	}
	std::cerr << "Unable to open file";
	return (false);
}


void Spawner::CreateLight(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_light", atoi(timing), _lowestmobid);
	_lowestmobid++;
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateMedium(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_medium", atoi(timing), _lowestmobid);
	_lowestmobid++;
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateHeavy(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_heavy", atoi(timing), _lowestmobid);
	_lowestmobid++;
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateBoss(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_boss", atoi(timing), _lowestmobid);
	_lowestmobid++;
	if (ret != NULL)
		_mobs.push_back(ret);
}


void Spawner::update(float begintime, float dtime, ServerMessage *message)
{
	//on check si tous les mobs du lvl sont finis et si oui on quit
	if (_mobs.size() == 0)
	{
		if (_level == 1)
			this->LoadMonsters("Level2.txt");
		else if (_level == 2)
			this->LoadMonsters("Level3.txt");
		else
			this->set_over(true, message);
		_level++;
	}

	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		if ((begintime / 1000000) >= _mobs[i]->get_time() && _mobs[i]->isAlive() == false) // s'il ne sont encor en vie
			_mobs[i]->set_alive(true);
		if (_mobs[i]->isAlive() == true) // si ils sont vivant
			_mobs[i]->update(dtime, message, _shots, &_lowestshotid);
		if (_mobs[i]->isDead() == true) // si ils sont mort
		{
			if (_mobs.size() == 1)
			{
				delete _mobs.at(0);
				_mobs.clear();
			}
			else
			{
				delete _mobs.at(i);
				_mobs.erase(_mobs.begin() + i);
			}
		}
	}
	//on check la collision des mobs
	this->collide(message);
	//on move les shots
	for (size_t i = 0; i < _shots.size(); i++)
		_shots[i].move(dtime);
	//on check leur mort
	this->check_shots_death();
	//on ecrit les shots
	this->write_shots(message);
	//on ecrit les mobs
	this->write_mobs(message);

}

void	Spawner::write_shots(ServerMessage *message)
{
	int		count = 0;

	//on reset les shots
	for (size_t i = 0; i < 100; i++)
		for (size_t j = 0; j < 6; j++)
			message->shots[i][j] = -1;

	for (size_t i = 0; i < _shots.size() && i < 100; ++i)
	{
		if (_shots[i].is_alive() == true) // pour chaque shots en vie on write ses infos
		{
			message->shots[count][TYPE] = _shots[i].get_type();
			message->shots[count][ID] = _shots[i].get_id();
			message->shots[count][POS_X] = _shots[i].get_pos_x();
			message->shots[count][POS_Y] = _shots[i].get_pos_y();
			message->shots[count][DIR_X] = _shots[i].get_dir_x();
			message->shots[count][DIR_Y] = _shots[i].get_dir_y();
			count++;
		}
	}
}

void	Spawner::write_mobs(ServerMessage *message)
{
	int		count = 0;
	// on mets tous les champs a -1
	for (size_t i = 0; i < 30; i++)
		for (size_t j = 0; j < 6; j++)
			message->monsters[i][j] = -1;

	for (unsigned int i = 0; i < _mobs.size() && i < 30; ++i)
	{
		if (_mobs[i]->isAlive() == true) // pour chaque mob en vie on write ses infos
		{
			message->monsters[count][TYPE] = _mobs[i]->get_type();
			message->monsters[count][ID] = _mobs[i]->get_id();
			message->monsters[count][POS_X] = _mobs[i]->get_pos_x();
			message->monsters[count][POS_Y] = _mobs[i]->get_pos_y();
			message->monsters[count][DIRECTION] = _mobs[i]->get_direction();
			//message->monsters[count][HP] = _mobs[i]->get_hp(); => a faire plus tard
			count++;
		}
	}
}

void	Spawner::check_shots_death()
{
	//on suprime les shots qui doivent l'être
	for (size_t i = 0; i < _shots.size(); i++)
		if (_shots[i].is_alive() == false) // si ils sont mort
		{
			if (_shots.size() == 1)
				_shots.clear();
			else
				_shots.erase(_shots.begin() + i);
		}
}

bool	Spawner::is_over() const
{
	return (_over);
}

void	Spawner::set_over(bool over, ServerMessage *mess)
{
	_over = over;
	mess->is_game_over = true;
}

void	Spawner::create_shot(int type, int dmg, int x, int y, int vec_x, int vec_y)
{
	Shots	newshot(_lowestshotid, type, dmg, x, y, vec_x, vec_y);

	_lowestshotid++;
	_shots.push_back(newshot);
}

void	Spawner::collide(ServerMessage *mess)
{
	// pour tous les mobs
	for (size_t i = 0; i < _mobs.size(); i++)
	{
		if (_mobs[i]->isAlive() == true)
		{
			//collision avec les  balles
			for (size_t j = 0; j < _shots.size(); j++)
			{
				if (_shots[j].get_type() == ALLY && _mobs[i]->checkCollision(2, _shots[j].get_pos_x(), _shots[j].get_pos_y()) == true)
				{
					_mobs[i]->hitme(_shots[j].get_dmg());
					_shots[j].set_alive(false);
				}
			}

			//collision avec les joueurs
			for (size_t j = J1; j <= J4; j++)
			{
				if (_mobs[i]->checkCollision(2, mess->posx[j], mess->posy[j]) == true)
				{
					_mobs[i]->hitme(_mobs[i]->get_health() + 1);
					mess->current_hp[j] -= 4;
					//provoquer la mort du joueur si sa vie drop trop bas
				}
			}
		}
	}
}