#pragma once
#include "AMenu.hpp"

class LoginMenu :
	public AMenu
{
protected:
	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room);
	virtual AMenu	*myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room);
public:
	LoginMenu(void);
	~LoginMenu(void);
};

