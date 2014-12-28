#pragma once

#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "AMonster.h"
#include "ServerMessage.h"
#include "IDllLoader.h"
#include "Shots.h"

class Spawner;

typedef void (Spawner::*FuncType)(const char *arg);

class Spawner
{
private:
	std::vector<AMonster *>				_mobs;
	std::vector<Shots>					_shots;
	std::map<std::string, FuncType>		_monster_creation;
	IDllLoader							*_LibLoader;
	int									_lowestmobid;
	int									_lowestshotid;
	int									_level;
	bool								_over;

protected:
	void		CreateLight(const char *timing);
	void		CreateMedium(const char *timing);
	void		CreateHeavy(const char *timing);
	void		CreateBoss(const char *timing);

public:
	Spawner();
	~Spawner();

	bool		LoadMonsters(const char *filename);
	void		update(float begintime, float dtime, ServerMessage *message);
	void		write_mobs(ServerMessage *message);
	void		write_shots(ServerMessage *message);
	bool		is_over() const;
	void		set_over(bool over, ServerMessage *mess);
	void		create_shot(int type, int dmg, int x, int y, int vec_x, int vec_y);
	void		check_shots_death();
	void		add_mobs_shots(ServerMessage *message);
	void		collide(ServerMessage *message);
};

