#include "stdafx.h"
#include "AMonster.h"

AMonster::AMonster(int time)
: _timing(time)
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

bool AMonster::isAlive(int time)
{
	if (time >= _timing && _dead == false)
	{
		_alive = true;
		return (true);
	}
	return (false);
}

bool AMonster::isDead()
{
	return (_dead);
}

void AMonster::Die()
{
	_dead = true;
	_alive = false;
}

void AMonster::afftiming()
{
	std::cout << "timing = " << _timing << std::endl;
}