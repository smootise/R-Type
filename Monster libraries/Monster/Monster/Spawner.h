#pragma once

#include <vector>
#include <string>
#include "Monster.h"

class Spawner
{
	std::vector<Monster> _mobs;
public:
	Spawner();
	Spawner(char* file);
	~Spawner();
	void update();
	void draw();
};

