#pragma once
#include "AMenu.hpp"
class JoinRoomMenu :
	public AMenu
{
protected:
	int		leftOrRight;
	AMenu	*createRooms(std::vector<std::string> *availlablerooms);
	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room);
	virtual AMenu	*myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room);
public:
	JoinRoomMenu(void);
	~JoinRoomMenu(void);
};

