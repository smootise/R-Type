// M_lightDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_light.h"

M_light::M_light(int time) : AMonster(time)
{
	std::cout << "Creation of a GOOD Monster" << std::endl;
}

M_light::~M_light()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_light::update()
{
	std::cout << "udpate the monster" << std::endl;
}

extern "C"
{
	__declspec(dllexport) M_light			*create(int time)
	{
		M_light		*ret = NULL;

		ret = new M_light(time);
		return (ret);
	}
}