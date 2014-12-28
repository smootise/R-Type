// M_lightDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_light.h"

M_light::M_light(int time, int id) : AMonster(time, LIGHT, id)
{
	_target = -1;
	_speed = 0.006f;
	_health = 1;
	_dmg = 1;
	_fire_rate = 0;
	//_size = ;
	setPosition(time);
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_light::~M_light()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_light::update(float dtime, ServerMessage *message)
{
	std::cout << "udpate the monster" << std::endl;
	setTarget(dtime, message);
	tryMove(message->posx[_target], message->posy[_target]);
}

void M_light::setPosition(int time)
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

void M_light::setTarget(float dtime, ServerMessage *message)
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

void M_light::tryMove(float target_x, float target_y)
{
	if (target_x > _x && target_y > _y)
		_direction = BotRight;
	else if (target_x > _x && target_y < _y)
		_direction = UpRight;
	else if (target_x < _x && target_y > _y)
		_direction = BotLeft;
	else if (target_x < _x && target_y < _y)
		_direction = UpLeft;
	else if (target_x > _x)
		_direction = Bot;
	else if (target_x < _x)
		_direction = Up;
	else if (target_y > _y)
		_direction = Right;
	else if (target_y < _y)
		_direction = Left;
}

extern "C"
{
	__declspec(dllexport) M_light			*create(int time, int id)
	{
		M_light		*ret = NULL;

		ret = new M_light(time, id);
		return (ret);
	}
}