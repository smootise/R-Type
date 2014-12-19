#include "Spawner.h"


Spawner::Spawner()
{
}


Spawner::~Spawner()
{
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