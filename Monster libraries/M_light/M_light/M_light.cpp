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
	_size = 100;
	setPosition(time);
}

M_light::~M_light()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_light::update(float dtime, ServerMessage *message)
{
	setTarget(dtime, message);
	tryMove(message->posx[_target], message->posy[_target]);
	setMovement(_direction, _x, _y);
	move(dtime);
}

void M_light::setPosition(int time)
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

void M_light::setTarget(float dtime, ServerMessage *message)
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