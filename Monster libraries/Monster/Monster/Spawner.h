#pragma once

#include <vector>
#include <string>
#include "Monster.h"

class Spawner
{
	std::vector<Monster> mobs;
public:
	Spawner(std::string file);
	~Spawner();
	void update();
	void draw();
};

