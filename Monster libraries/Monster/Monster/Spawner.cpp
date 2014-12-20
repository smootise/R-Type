#include "Spawner.h"
#include <iostream>

Spawner::Spawner()
{
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