#include "M_medium.h"
#include <iostream>

M_medium::M_medium(int time) : Monster(time)
{
	std::cout << "M_Medium created !" << std::endl;
}

M_medium::~M_medium()
{
}
