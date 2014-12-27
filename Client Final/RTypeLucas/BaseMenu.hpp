#pragma once
#include "Amenu.hpp"
#include "LoginMenu.hpp"

class BaseMenu :
	public AMenu
{
protected:
	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
public:
	BaseMenu(void);
	~BaseMenu(void);

};

