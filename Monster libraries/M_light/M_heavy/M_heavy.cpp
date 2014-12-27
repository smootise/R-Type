// M_heavyDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_heavy.h"

M_heavy::M_heavy(int time) : AMonster(time, HEAVY)
{
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_heavy::~M_heavy()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_heavy::update(float dtime, ServerMessage message)
{
	std::cout << "udpate the monster" << std::endl;
	setTarget(dtime, message);
	tryMove(dtime, message.posx[_target], message.posy[_target]);
}

void M_heavy::tryMove(float dtime, float target_x, float target_y)
{
	if (target_y > _y)
		;//setmoves(2);
	else if (target_y < _y)
		;//setmoves(8);
	else
		tryShoot(dtime, 0);
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

void M_heavy::setTarget(float dtime, ServerMessage message)
{
	if (_target != -1 && message.name[_target] != "DefaultName")
		return ;
	if ((int)(dtime * 100) % 2 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (message.name[i] != "DefaultName")
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
			if (message.name[i] != "DefaultName")
			{
				_target = i;
				return ;
			}
		}
	}
}

extern "C"
{
	__declspec(dllexport) M_heavy			*create(int time)
	{
		M_heavy		*ret = NULL;

		ret = new M_heavy(time);
		return (ret);
	}
}



