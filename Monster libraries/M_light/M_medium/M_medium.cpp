// M_mediumDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_medium.h"

M_medium::M_medium(int time, int id) : AMonster(time, MEDIUM, id)
{
	_speed = 0.001f;
	_health = 6;
	_dmg = 1;
	_fire_rate = 1000000;
	_size = 94;
	_going_up = true;
	_cd = _fire_rate;
	setPosition(time);
}

M_medium::~M_medium()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_medium::update(float dtime, ServerMessage *message, std::vector<Shots> &shots, int *lowestshotid)
{
	tryMove();
	tryShoot(dtime, shots, lowestshotid);
	//setMovement(_direction, _x, _y);
	move(dtime);
}

void M_medium::setPosition(int time)
{
	if (time % 2 == 0)
	{
		_x = 960 - _size;
		_y = 0;
	}
	else
	{
		_x = 960 - _size;
		_y = 540 - _size;
	}
}

void M_medium::tryMove()
{
	if (_going_up == true)
	{
		if (_y <= 0)
		{
			_going_up = false;
			_direction = Bot;
		}
		else
		{
			_direction = Up;
		}
	}
	else
	{
		if (_y >= 540 - _size)
		{
			_going_up = true;
			_direction = Up;
		}
		else
			_direction = Bot;
	}
}

void M_medium::tryShoot(float dtime, std::vector<Shots> &shots, int *lowestshotid)
{
	if (_cd <= 0)
	{
		//this->shoot(shots, lowestshotid, -1, 0); // vers la gauche 
		std::cout << "PAN" << std::endl;
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