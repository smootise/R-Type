#include "Monster.h"
#include <iostream>


Monster::Monster()
{
	std::cout << "Creation of a Monster" << std::endl;
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

M_light::M_light(){}

M_light::~M_light(){}

M_heavy::M_heavy(){}

M_heavy::~M_heavy(){}

M_medium::M_medium(){}

M_medium::~M_medium(){}

M_boss::M_boss(){}

M_boss::~M_boss(){}
