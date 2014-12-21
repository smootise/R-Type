#include "Spawner.h"
#include "Monster.h"
#include "M_boss.h"
#include "M_heavy.h"
#include "M_medium.h"
#include "M_light.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

Spawner::Spawner(char* fileName)
{
	_monster_creation["light"] = &Spawner::CreateLight;
	_monster_creation["medium"] = &Spawner::CreateMedium;
	_monster_creation["heavy"] = &Spawner::CreateHeavy;
	_monster_creation["boss"] = &Spawner::CreateBoss;

	LoadMonsters(fileName);

	std::cout << "Creation of a Mob Spawner !" << std::endl;
}

Spawner::~Spawner()
{
	std::cout << "The Mob Spawner is down !" << std::endl;
}

bool Spawner::LoadMonsters(char *fileName)
{
	int line_nbr;
	std::string line;
	std::string timing;
	std::string type;
	std::ifstream myfile(fileName);

	line_nbr = 1;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.empty() == false && line[0] != '#')
			{
				timing = line.substr(line.find_first_of(":") + 1, 5);
				type = line.substr(0, line.find_first_of(":"));
				std::cout << "type :" << type << ", timing :" << timing << std::endl;
				if (_monster_creation.count(type) > 0)
					(this->*_monster_creation[type])(timing.c_str());
				else
				{
					std::cout << "error : line " << line_nbr << " is corrupted." << std::endl;
					return (false);
				}
			}
			line_nbr = line_nbr + 1;
		}
		myfile.close();
		return (true);
	}
	std::cout << "Unable to open file";
	return (false);
}

void Spawner::CreateLight(const char *timing)
{
	_mobs.push_back(new M_light(atoi(timing)));
}

void Spawner::CreateMedium(const char *timing)
{
	_mobs.push_back(new M_medium(atoi(timing)));
}

void Spawner::CreateHeavy(const char *timing)
{
	_mobs.push_back(new M_heavy(atoi(timing)));
}

void Spawner::CreateBoss(const char *timing)
{
	_mobs.push_back(new M_boss(atoi(timing)));
}

void Spawner::update()
{
	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		_mobs[i]->update();
	}
}

void Spawner::draw()
{
	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		_mobs[i]->draw();
	}
}

void Spawner::afftiming()
{
	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		_mobs[i]->afftiming();
	}
}