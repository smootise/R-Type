#pragma once

#include <vector>
#include "Monster.h"

class Spawner
{
	std::vector<Monster> mobs;
public:
	Spawner();
	~Spawner();
	void update();
	void draw();
};

