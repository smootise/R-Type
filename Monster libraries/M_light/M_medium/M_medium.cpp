// M_mediumDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_medium.h"

M_medium::M_medium(int time, int id) : AMonster(time, MEDIUM, id)
{
	_speed = 0.004f;
	_health = 2;
	_dmg = 1;
	_fire_rate = 1.0f;
	//_size = ;
	_going_up = true;
	_cd = _fire_rate;
	setPosition(time);
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_medium::~M_medium()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_medium::update(float dtime, ServerMessage *message)
{
	std::cout << "udpate the monster" << std::endl;
	tryMove();
	tryShoot(dtime);
}

void M_medium::setPosition(int time)
{
	if (time % 2 == 0)
	{
		_x = 500;
		_y = 20;
	}
	else
	{
		_x = 500;
		_y = 120;
	}
}

void M_medium::tryMove()
{
	if (_going_up == true)
	{
		if (_y <= 0)
			_going_up = false;
		else
			_direction = Up;
	}
	else
	{
		if (_y >= 100)
			_going_up = true;
		else
			_direction = Bot;
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
	__declspec(dllexport) M_medium			*create(int time, int id)
	{
		M_medium		*ret = NULL;

		ret = new M_medium(time, id);
		return (ret);
	}
}