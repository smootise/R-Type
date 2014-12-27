// M_bossDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_boss.h"

M_boss::M_boss(int time, int id) : AMonster(time, BOSS, id)
{
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_boss::~M_boss()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_boss::update(float dtime, ServerMessage message)
{
	std::cout << "udpate the monster" << std::endl;
}

extern "C"
{
	__declspec(dllexport) M_boss			*create(int time)
	{
		M_boss		*ret = NULL;

		ret = new M_boss(time);
		return (ret);
	}
}