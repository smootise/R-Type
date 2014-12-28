// M_heavyDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_heavy.h"

M_heavy::M_heavy(int time, int id) : AMonster(time, HEAVY, id)
{
	_speed = 0.004f;
	_health = 3;
	_dmg = 1;
	_fire_rate = 2.0f;
	//_size = ;
	_cd = _fire_rate;
	_target = -1;
	setPosition(time);
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_heavy::~M_heavy()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_heavy::update(float dtime, ServerMessage *message)
{
	std::cout << "udpate the monster" << std::endl;
	setTarget(dtime, message);
	tryMove(dtime, message->posx[_target], message->posy[_target]);
}

void M_heavy::setPosition(int time)
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

void M_heavy::tryMove(float dtime, float target_x, float target_y)
{
	if (target_y > _y)
		_direction = Bot;
	else if (target_y < _y)
		_direction = Up;
	else
	{
		_direction = Default;
		tryShoot(dtime, 0);
	}
	tryShoot(dtime, 1);
}

void M_heavy::tryShoot(float dtime, int i)
{
	if (_cd <= 0)
	{
		//shoot();
		_cd = _fire_rate;
	}
	if (i == 1)
		_cd = _cd - dtime;
}

void M_heavy::setTarget(float dtime, ServerMessage *message)
{
	if (_target != -1 && message->name[_target] != "DefaultName")
		return ;
	if ((int)(dtime * 100) % 2 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (message->name[i] != "DefaultName")
			{
				_target = i;
				return ;
			}
		}
	}
	else
	{
			for (int i = 3; i >= 0; i--)
		{
			if (message->name[i] != "DefaultName")
			{
				_target = i;
				return ;
			}
		}
	}
}

extern "C"
{
	__declspec(dllexport) M_heavy			*create(int time, int id)
	{
		M_heavy		*ret = NULL;

		ret = new M_heavy(time, id);
		return (ret);
	}
}



