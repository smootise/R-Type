#include "Spawner.h"
#include "AMonster.h"

#ifdef _WIN32
	#include "WinDllLoader.h"
#else
	#include "LinDllLoader.h"
#endif


Spawner::Spawner()
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

	ret = _LibLoader->get_instance("Libs/M_light", atoi(timing));
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateMedium(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_medium", atoi(timing));
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateHeavy(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_heavy", atoi(timing));
	if (ret != NULL)
		_mobs.push_back(ret);
}

void Spawner::CreateBoss(const char *timing)
{
	AMonster	*ret = NULL;

	ret = _LibLoader->get_instance("Libs/M_boss", atoi(timing));
	if (ret != NULL)
		_mobs.push_back(ret);
}


void Spawner::update(float begintime, float dtime, ServerMessage *message)
{
	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		if ((begintime / 100000) >= _mobs[i]->get_time() && _mobs[i]->isAlive() == false) // s'il ne sont encor en vie
			_mobs[i]->set_alive(true);
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
}
