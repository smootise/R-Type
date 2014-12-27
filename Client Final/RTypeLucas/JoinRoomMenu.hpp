#pragma once
#include "AMenu.hpp"
class JoinRoomMenu :
	public AMenu
{
protected:
	int		leftOrRight;
	bool	firstTry;
	AMenu	*createRooms(std::vector<std::string> *availlablerooms);
	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
	virtual AMenu	*myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
public:
	JoinRoomMenu(void);
	~JoinRoomMenu(void);
};

