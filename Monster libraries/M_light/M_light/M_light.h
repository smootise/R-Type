#pragma once

#include "AMonster.h"

class M_light : public AMonster
{
private:
	int _target;
public:
	M_light(int time);
	~M_light();

	void			update(float dtime, ServerMessage message);
	void			tryMove(float target_x, float target_y);
	void			setTarget(float dtime, ServerMessage message);
};