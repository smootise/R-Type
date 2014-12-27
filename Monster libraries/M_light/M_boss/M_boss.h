#pragma once

#include "AMonster.h"

class M_boss : public AMonster
{
public:
	M_boss(int time, int id);
	~M_boss();

	void			update(float dtime, ServerMessage message);
};