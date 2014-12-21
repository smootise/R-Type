#include "Spawner.h"
#include "Monster.h"
#include "M_boss.h"
#include "M_heavy.h"
#include "M_medium.h"
#include "M_light.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Spawner::Spawner()
{
	std::cout << "Creation of a Mob Spawner !" << std::endl;
}

Spawner::Spawner(char* fileName)
{
	std::size_t length;
	char type[10];
	char timing[10];
	std::string line;
	std::ifstream myfile(fileName);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.empty() == false && line[0] != '#')
			{
				length = line.copy(type, line.find_first_of(":"));
				type[length] = '\0';
				length = line.copy(timing, 10, line.find_first_of(":"));
				timing[length] = '\0';
				std::cout << "type : " << type << ", timing : " << timing << std::endl;
				if (line.compare("light"))
					_mobs.push_back(M_light(atoi(timing)));
				if (line.compare("medium"))
					_mobs.push_back(M_medium(atoi(timing)));
				if (line.compare("heavy"))
					_mobs.push_back(M_heavy(atoi(timing)));
				if (line.compare("boss"))
					_mobs.push_back(M_boss(atoi(timing)));
			}
		}
		myfile.close();
	}

	else std::cout << "Unable to open file";


	std::cout << "Creation of a Mob Spawner !" << std::endl;
}

Spawner::~Spawner()
{
	std::cout << "The Mob Spawner is down !" << std::endl;
}

void Spawner::update()
{
	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		_mobs[i].update();
	}
}

void Spawner::draw()
{
	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		_mobs[i].draw();
	}
}

void Spawner::afftiming()
{
	for (unsigned int i = 0; i < _mobs.size(); ++i)
	{
		_mobs[i].afftiming();
	}
}