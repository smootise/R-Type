#pragma once
#include "AMenu.hpp"

class CreateRoomMenu :
	public AMenu
{
protected:
	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
	virtual AMenu	*myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
public:
	CreateRoomMenu(void);
	~CreateRoomMenu(void);

};

