// M_mediumDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_medium.h"

M_medium::M_medium(int time, int id) : AMonster(time, MEDIUM, id)
{
	//set les parametres Monsters;

	_going_up = true;
	_cd = _fire_rate;
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_medium::~M_medium()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_medium::update(float dtime, ServerMessage message)
{
	std::cout << "udpate the monster" << std::endl;
	tryMove();
	tryShoot(dtime);
}

void M_medium::tryMove()
{
	if (_going_up == true)
	{
		if (_y <= 0)
			_going_up = false;
		else
			;//setdirection(8);
	}
	else
	{
		if (_y >= 100)
			_going_up = true;
		else
			;//setdirection(2);
	}
}

void M_medium::tryShoot(float dtime)
{
	if (_cd <= 0)
	{
		//shoot();
		_cd = _fire_rate;
	}
	else
		_cd = _cd - dtime;
}

extern "C"
{
	__declspec(dllexport) M_medium			*create(int time)
	{
		M_medium		*ret = NULL;

		ret = new M_medium(time);
		return (ret);
	}
}