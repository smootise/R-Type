#include "RoomFirstMenu.hpp"
#include "BaseMenu.hpp"
#include "CreateRoomMenu.hpp"
#include "JoinRoomMenu.hpp"

AMenu	*RoomFirstMenu::onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
			std::vector<std::string> *availlablerooms, Room	*room, std::string *name)
{
	if (selected == 0)
		return (new CreateRoomMenu());
	if (selected == 1)
		return (new JoinRoomMenu());
	if (selected == 2)
		return (new BaseMenu());
	return (NULL);
}

RoomFirstMenu::RoomFirstMenu(void)
{
	Menu.push_back(new HudWindow("Creer une\npartie", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 162,
		WIDTH / 2, 108));
	Menu.push_back(new HudWindow("Rejoindre une\npartie", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 54,
		WIDTH / 2, 108));
	Menu.push_back(new HudWindow("Quitter", WIDTH / 2 - WIDTH / 4, LENGTH / 2 + 54,
		WIDTH / 2, 108));
}


RoomFirstMenu::~RoomFirstMenu(void)
{
}
