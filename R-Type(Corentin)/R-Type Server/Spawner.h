#pragma once

#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "AMonster.h"
#include "IDllLoader.h"

class Spawner;

typedef void (Spawner::*FuncType)(const char *arg);

class Spawner
{
private:
	std::vector<AMonster *>				_mobs;
	std::map<std::string, FuncType>		_monster_creation;
	IDllLoader							*_LibLoader;

protected:
	void		CreateLight(const char *timing);
	void		CreateMedium(const char *timing);
	void		CreateHeavy(const char *timing);
	void		CreateBoss(const char *timing);

public:
	Spawner();
	~Spawner();

	bool		LoadMonsters(const char *filename);
	void		update();
};
