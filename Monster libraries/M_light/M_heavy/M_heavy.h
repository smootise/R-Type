#pragma once

#include "AMonster.h"

class M_heavy : public AMonster
{
public:
	M_heavy(int time);
	~M_heavy();

	void			update();
};