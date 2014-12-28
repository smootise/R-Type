#pragma once

#include "AMonster.h"

class M_heavy : public AMonster
{
private:
	float _cd;
	int _target;
public:
	M_heavy(int time, int id);
	~M_heavy();

	void			update(float dtime, ServerMessage *message);
	void			tryMove(float dtime, float target_x, float target_y);
	void			setTarget(float dtime, ServerMessage *message);
	void			setPosition(int time);
	void			tryShoot(float dtime, int i);
};