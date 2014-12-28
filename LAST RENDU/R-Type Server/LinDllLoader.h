#pragma once
#include <dlfcn.h>
#include "IDllLoader.h"

typedef std::map<std::string, void *>::iterator	it_type;

class LinDllLoader : public IDllLoader
{
protected:
	std::map<std::string, void *>	_availlable_libs;

public:
	LinDllLoader();
	virtual ~LinDllLoader();

	virtual void		loadfromfile(const std::string &filename);
	virtual	AMonster	*get_instance(const std::string &type, int timing, int id);
};

