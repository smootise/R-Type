#include "Monster.h"
#include <iostream>

Monster::Monster(int time)
	:	_timing(time)
{
	_alive = false;
	_dead = false;
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

Monster::~Monster()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void Monster::move(float x, float y)
{
	std::cout << "Move the GodDamn monster !" << std::endl;
}

bool Monster::isAlive(int time)
{
	if (time >= _timing && _dead == false)
	{
		_alive = true;
		return (true);
	}
	return (false);
}

bool Monster::isDead()
{
	return (_dead);
}

void Monster::Die()
{
	_dead = true;
	_alive = false;
}

void Monster::update()
{
	if (_alive == false)
		return ;
	std::cout << "This Monster has been updated" << std::endl;
}

void Monster::draw()
{
	std::cout << "This Monster has been redrawn" << std::endl;
}

void Monster::afftiming()
{
	std::cout << "timing = " << _timing << std::endl;
}