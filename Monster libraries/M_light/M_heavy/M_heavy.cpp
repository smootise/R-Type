// M_heavyDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_heavy.h"

M_heavy::M_heavy(int time) : AMonster(time)
{
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_heavy::~M_heavy()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_heavy::update()
{
	std::cout << "udpate the monster" << std::endl;
}

extern "C"
{
	__declspec(dllexport) M_heavy			*create(int time)
	{
		M_heavy		*ret = NULL;

		ret = new M_heavy(time);
		return (ret);
	}
}



