#include "LoginMenu.hpp"
#include "BaseMenu.hpp"
#include "RoomFirstMenu.hpp"

LoginMenu::LoginMenu(void)
{
	Hud.push_back(new HudWindow("Nom d'utilisateur:", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 162,
		WIDTH / 2, 108));
	Menu.push_back(new HudTextField(24, "", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 54,
		WIDTH / 2, 108));
	Menu.push_back(new HudWindow("Retour", WIDTH / 2 - WIDTH / 4, LENGTH / 2 + 54,
		WIDTH / 2, 108));
}

LoginMenu::~LoginMenu(void)
{
}

AMenu	*LoginMenu::myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room)
{
	if (state["Logged"] == true)
		return (new RoomFirstMenu());
	if (inLoading == false)
		return (NULL);
	if (state["Pending"] == false)
	{
		if (state["Logged"] == true)
			return (new RoomFirstMenu());
		inLoading = false;
		Hud[0]->setText("Nom d'utilisateur invalide");
	}
	return (NULL);
}

AMenu	*LoginMenu::onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room)
{
	if (inLoading == true)
		return (NULL);
	if (selected == 0 && Menu[0]->getText().size() >= 3)
	{
		inLoading = true;
		comhandler->SendCommand(LOGIN, new std::string(Menu[0]->getText()));
	}
	if (selected == 1)
		return (new BaseMenu());
	return (NULL);
}