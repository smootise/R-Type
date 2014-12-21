#pragma once

#include <vector>
#include <map>
#include <string>
#include "Monster.h"

/*enum
{
	LIGHT,
	MEDIUM,
	HEAVY,
	BOSS,
};*/

class Spawner;

typedef void (Spawner::*FuncType)(const char *arg);

class Spawner
{
private:
	std::vector<Monster *>				_mobs;
	std::map<std::string, FuncType>		_monster_creation;
protected:
	void CreateLight(const char *timing);
	void CreateMedium(const char *timing);
	void CreateHeavy(const char *timing);
	void CreateBoss(const char *timing);
public:
	Spawner(char* file);
	~Spawner();
	bool LoadMonsters(char *filename);
	void update();
	void draw();
	void afftiming();
};

