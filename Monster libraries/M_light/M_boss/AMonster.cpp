#include "stdafx.h"
#include "AMonster.h"

AMonster::AMonster(int time, int type, int id)
: _timing(time), _type(type), _id(id)
{
	_alive = false;
	_dead = false;
	std::cout << "Creation of a GOOD Monster (father)" << std::endl;
}

AMonster::~AMonster()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void AMonster::move(float x, float y)
{
	std::cout << "Move the GodDamn monster !" << std::endl;
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