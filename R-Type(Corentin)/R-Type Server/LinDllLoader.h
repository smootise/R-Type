#pragma once
#include "IDllLoader.h"

typedef std::map<std::string, void *>::iterator	it_type;

class LinDllLoader : public IDllLoader
{
public:
	LinDllLoader();
	virtual ~LinDllLoader();
};

