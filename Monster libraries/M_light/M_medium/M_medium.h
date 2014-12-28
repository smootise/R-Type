#pragma once

#include "AMonster.h"

class M_medium : public AMonster
{
private:
	bool _going_up;
	float _cd;
public:
	M_medium(int time, int id);
	~M_medium();

	void tryMove();
	void tryShoot(float dtime);
	void setPosition(int time);
	void update(float dtime, ServerMessage *message);
};