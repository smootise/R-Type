#pragma once

#include "AMonster.h"

class M_medium : public AMonster
{
public:
	M_medium(int time);
	~M_medium();

	void			update();
};