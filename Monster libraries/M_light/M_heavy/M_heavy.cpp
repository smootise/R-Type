// M_heavyDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_heavy.h"

M_heavy::M_heavy(int time, int id) : AMonster(time, HEAVY, id)
{
	_speed = 0.001f;
	_health = 9;
	_dmg = 1;
	_fire_rate = 2.0f;
	_size = 96;
	_cd = _fire_rate;
	_target = -1;
	setPosition(time);
}

M_heavy::~M_heavy()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_heavy::update(float dtime, ServerMessage *message)
{
	setTarget(dtime, message);
	tryMove(dtime, message->posx[_target], message->posy[_target]);
	setMovement(_direction, _x, _y);
	move(dtime);
}

void M_heavy::setPosition(int time)
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

void M_heavy::tryMove(float dtime, float target_x, float target_y)
{
	if (target_y > _y && _y < 540 - _size)
		_direction = Bot;
	else if (target_y < _y && _y > 0)
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
	std::string target_name(message->name[_target]);
	std::string default_name("DefaultName");

	if (_target != -1 && target_name != default_name)
		return ;
	if ((int)(dtime * 100) % 2 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			std::string name(message->name[i]);
			if (name != default_name)
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
			std::string name(message->name[i]);
			if (name != default_name)
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



