#include "Monster.h"
#include <iostream>

Monster::Monster(int time)
	:	_timing(time)
{
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

void Monster::update()
{
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