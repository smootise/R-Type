#pragma once

#include "AMonster.h"

class M_boss : public AMonster
{
public:
	M_boss(int time);
	~M_boss();

	void			update();
};