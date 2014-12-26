// M_mediumDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_medium.h"

M_medium::M_medium(int time) : AMonster(time)
{
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_medium::~M_medium()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_medium::update()
{
	std::cout << "udpate the monster" << std::endl;
}

extern "C"
{
	__declspec(dllexport) M_medium			*create(int time)
	{
		M_medium		*ret = NULL;

		ret = new M_medium(time);
		return (ret);
	}
}