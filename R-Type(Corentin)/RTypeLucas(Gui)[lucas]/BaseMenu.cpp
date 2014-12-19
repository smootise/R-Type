#include "BaseMenu.hpp"
#include "LoginMenu.hpp"

BaseMenu::BaseMenu(void) : AMenu()
{
	Hud.push_back(new HudWindow("RTYPE", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 216,
		WIDTH / 2, 108));
	Hud[0]->setColor(sf::Color(155, 155, 155, 255), sf::Color(155, 155, 155, 255));
	Hud[0]->setSelected(true);
	Menu.push_back(new HudWindow("Jouer", WIDTH / 2 - WIDTH / 4, LENGTH / 2 - 108,
		WIDTH / 2, 108));
	Menu.push_back(new HudWindow("Option", WIDTH / 2 - WIDTH / 4, LENGTH / 2,
		WIDTH / 2, 108));
	Menu.push_back(new HudWindow("Quitter", WIDTH / 2 - WIDTH / 4, LENGTH / 2 + 108,
		WIDTH / 2, 108));
}

BaseMenu::~BaseMenu(void)
{
}

AMenu	*BaseMenu::onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room)
{
	if (selected == 0)
		return (new LoginMenu());
	if (selected == 2)
		return this;
	return (NULL);
}