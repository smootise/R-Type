#pragma once

#include "AMonster.h"

class M_boss : public AMonster
{
private:
	bool _walking;
	float _cd;
	int _shot;
	int _shots;
	int _pos;
	int _tab[2][4];
public:
	M_boss(int time, int id);
	~M_boss();

	void			tryMove();
	void			tryShoot(float dtime);
	void			update(float dtime, ServerMessage *message);
};