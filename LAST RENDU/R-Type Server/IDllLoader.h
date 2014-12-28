#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include "AMonster.h"

class IDllLoader
{
public:
	virtual ~IDllLoader() { }

	virtual void		loadfromfile(const std::string &filename) = 0;
	virtual	AMonster	*get_instance(const std::string &type, int timing, int id) = 0;
};