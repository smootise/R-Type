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
	void tryShoot(float dtime, std::vector<Shots> &shots, int *lowestshotid);
	void setPosition(int time);
	void update(float dtime, ServerMessage *message, std::vector<Shots> &shots, int *lowestshotid);
};