#pragma once

#include "AMonster.h"

class M_light : public AMonster
{
public:
	M_light(int time);
	~M_light();

	void			update();
};