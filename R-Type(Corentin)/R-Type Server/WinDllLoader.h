#pragma once
#include <windows.h>
#include <stdio.h>
#include "IDllLoader.h"

typedef std::map<std::string, HINSTANCE>::iterator	it_type;

class WinDllLoader : public IDllLoader
{
protected:
	std::map<std::string, HINSTANCE>	_availlable_libs;
	
public:
	WinDllLoader();
	virtual ~WinDllLoader();
	
	virtual void		loadfromfile(const std::string &filename);
	virtual	AMonster	*get_instance(const std::string &type, int timing, int id);
};

