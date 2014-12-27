// M_lightDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_light.h"

M_light::M_light(int time, int id) : AMonster(time, LIGHT, id)
{
	_target = -1;
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_light::~M_light()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_light::update(float dtime, ServerMessage message)
{
	std::cout << "udpate the monster" << std::endl;
	setTarget(dtime, message);
	tryMove(message.posx[_target], message.posy[_target]);
}

void M_light::setTarget(float dtime, ServerMessage message)
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

void M_light::tryMove(float target_x, float target_y)
{
	if (target_x > _x && target_y > _y)
		;//setmove(3);
	else if (target_x > _x && target_y < _y)
		;//setmove(9);
	else if (target_x < _x && target_y > _y)
		;//setmove(1);
	else if (target_x < _x && target_y < _y)
		;//setmove(7);
	else if (target_x > _x)
		;//setmoves(2);
	else if (target_x < _x)
		;//setmoves(8);
	else if (target_y > _y)
		;//setmoves(6);
	else if (target_y < _y)
		;//setmoves(4);
}

extern "C"
{
	__declspec(dllexport) M_light			*create(int time)
	{
		M_light		*ret = NULL;

		ret = new M_light(time);
		return (ret);
	}
}