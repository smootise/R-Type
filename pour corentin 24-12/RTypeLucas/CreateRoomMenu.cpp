#include "CreateRoomMenu.hpp"
#include "RoomFirstMenu.hpp"
#include "InRoomMenu.hpp"

CreateRoomMenu::CreateRoomMenu(void)
{
	inLoading = false;
	Hud.push_back(new HudWindow("Nom de la room:", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 162,
		WIDTH / 2, 108));
	Menu.push_back(new HudTextField(24, "", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 54,
		WIDTH / 2, 108));
	Menu.push_back(new HudWindow("Retour", WIDTH / 2 - WIDTH / 4, LENGTH / 2 + 54,
		WIDTH / 2, 108));
}

CreateRoomMenu::~CreateRoomMenu(void)
{
}

AMenu	*CreateRoomMenu::myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name)
{
	if (inLoading == false)
		return (NULL);
	if (state["Pending"] == false)
	{
		if (room != NULL)
			return (new InRoomMenu());
		inLoading = false;
		Hud[0]->setText("Impossible de creer la room");
	}
	return (NULL);
}

AMenu	*CreateRoomMenu::onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room, std::string *name)
{
	if (inLoading == true)
		return (NULL);
	if (selected == 0 && Menu[0]->getText().size() >= 3)
	{
		inLoading = true;
		comhandler->SendCommand(CREATE_ROOM, new std::string(Menu[0]->getText()));
	}
	if (selected == 1)
		return (new RoomFirstMenu());
	return (NULL);
}