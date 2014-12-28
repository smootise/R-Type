#include "stdafx.h"
#include "AMonster.h"

AMonster::AMonster(int time, int type, int id)
: _timing(time), _type(type), _id(id)
{
	_alive = false;
	_dead = false;
}

AMonster::~AMonster()
{
	
}

void	AMonster::setMovement(int param, float startingX, float startingY)
{
	direction	tab[] = { BotLeft, Bot, BotRight, Left,	Default, Right,	UpLeft,	Up,	UpRight};

	if (param <= 0 || param >= 10)
		return;
	_direction = tab[param - 1];
	if (startingX >= 0)
		_x = startingX;
	if (startingY >= 0)
		_y = startingY;
}

void	AMonster::move(float dtime)
{
	float	dist;

	dist = dtime * _speed;
	if (_direction != 5)
	{
		//std::cout << dist << ":" << clock.getElapsedTime().asMicroseconds() << std::endl;
	}
	if (_direction % 2 == 1)
		dist /= 1.4f;
	if (_direction >= 7)
		_y -= dist;
	else if (_direction <= 3)
		_y += dist;
	if (_direction % 3 == 0)
		_x += dist;
	if (_direction % 3 == 1)
		_x -= dist;
	_x = (_x < 0) ? 0 : (_x >= 960) ? 960 - 1 : _x;
	_y = (_y < 0) ? 0 : (_y >= 540) ? 540 - 1 : _y;
}

void AMonster::set_alive(bool alive)
{
	_alive = alive;
}

bool AMonster::isAlive()
{
	if (_dead != false)
		return (_alive);
	return (false);
}

bool AMonster::isDead()
{
	return (_dead);
}

void	AMonster::Die()
{
	_dead = true;
	_alive = false;
}

int		AMonster::get_time() const
{
	return (_timing);
}

int		AMonster::get_type() const
{
	return (_type);
}

int		AMonster::get_pos_x() const
{
	return ((int)_x);
}

int		AMonster::get_pos_y() const
{
	return ((int)_y);
}

int		AMonster::get_direction() const
{
	return (_direction);
}

int		AMonster::get_id() const
{
	return (_id);
}