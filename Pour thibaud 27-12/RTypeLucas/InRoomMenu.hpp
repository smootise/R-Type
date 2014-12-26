#pragma once
#include "AMenu.hpp"
class InRoomMenu :
	public AMenu
{
protected:
	int		updateDelta;
	bool	updateName(int, Room *, std::string *);
	bool	AlignLeft;
	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
	virtual AMenu	*myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
public:
	InRoomMenu(void);
	~InRoomMenu(void);
};

