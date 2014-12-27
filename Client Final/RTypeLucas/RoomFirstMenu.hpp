#pragma once
#include "AMenu.hpp"

class RoomFirstMenu :
	public AMenu
{
protected:
	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
			  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
public:
	RoomFirstMenu(void);
	~RoomFirstMenu(void);
};

