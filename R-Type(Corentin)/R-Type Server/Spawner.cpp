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
	_lowestid = 1;
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

	ret = _LibLoader->get_instance("Libs/M_light", atoi(timing), _lowestid);
	_lowestid++;
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateMedium(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_medium", atoi(timing), _lowestid);
	_lowestid++;
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateHeavy(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_heavy", atoi(timing), _lowestid);
	_lowestid++;
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateBoss(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_boss", atoi(timing), _lowestid);
	_lowestid++;
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
		{
			_mobs[i]->set_alive(true);
			std::cout << "je mets un mob alive" << std::endl;
		}
		if (_mobs[i]->isAlive() == true) // si ils sont vivant
			_mobs[i]->update(dtime, message);
		if (_mobs[i]->isDead() == true) // si ils sont mort
		{
			if (_mobs.size() == 1)
			{
				delete _mobs.at(0);
				_mobs.clear();
			}
			delete _mobs.at(i);
			_mobs.erase(_mobs.begin() + i);
		}
	}
	this->write_mobs(message);
}

void	Spawner::write_mobs(ServerMessage *message)
{
	int		count = 0;
	// on mets tous les champs a -1
	for (size_t i = 0; i < 30; i++)
		for (size_t j = 0; j < 6; j++)
			message->monsters[i][j] = -1;

	for (unsigned int i = 0; i < _mobs.size(); ++i)
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

bool	Spawner::is_over() const
{
	return (_over);
}

void	Spawner::set_over(bool over, ServerMessage *mess)
{
	_over = over;
	mess->is_game_over = true;
}
