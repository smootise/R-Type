#include <iostream>
#include "M_light.h"


M_light::M_light()
{
}

M_light::M_light(int time)
{
	_timing = time;
	std::cout << "M_light created !" << std::endl;
}

M_light::~M_light()
{
}
