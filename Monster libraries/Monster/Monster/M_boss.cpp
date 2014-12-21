#include "M_boss.h"
#include <iostream>

M_boss::M_boss(int time) : Monster(time)
{
	std::cout << "M_Boss created !" << std::endl;
}

M_boss::~M_boss()
{
}