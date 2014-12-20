#include "Spawner.h"
#include <iostream>
#include <fstream>

Spawner::Spawner()
{
	std::cout << "Creation of a Mob Spawner !" << std::endl;
}

Spawner::Spawner(char* fileName)
{
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << std::endl;
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
	for (unsigned int i = 0; i < mobs.size(); ++i)
	{
		mobs[i].update();
	}
}

void Spawner::draw()
{
	for (unsigned int i = 0; i < mobs.size(); ++i)
	{
		mobs[i].draw();
	}
}