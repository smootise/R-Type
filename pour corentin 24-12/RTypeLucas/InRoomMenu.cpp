#include "InRoomMenu.hpp"
#include "JoinRoomMenu.hpp"

InRoomMenu::InRoomMenu(void)
{
	updateDelta = 0;
	AlignLeft = true;
	Menu.push_back(new HudWindow("Start", WIDTH / 6, LENGTH / 6 + (LENGTH * 0 / 9),
		WIDTH / 3, LENGTH * 2 / 9));
	Menu.push_back(new HudWindow("Retour", WIDTH / 6, LENGTH / 6 + (LENGTH * 2 / 9),
		WIDTH / 3, LENGTH * 2 / 9));
	Hud.push_back(new HudWindow("", WIDTH / 2, LENGTH / 6 + (LENGTH * 0 / 6), WIDTH / 3, LENGTH / 6));
	Hud.push_back(new HudWindow("", WIDTH / 2, LENGTH / 6 + (LENGTH * 1 / 6), WIDTH / 3, LENGTH / 6));
	Hud.push_back(new HudWindow("", WIDTH / 2, LENGTH / 6 + (LENGTH * 2 / 6), WIDTH / 3, LENGTH / 6));
	Hud.push_back(new HudWindow("", WIDTH / 2, LENGTH / 6 + (LENGTH * 3 / 6), WIDTH / 3, LENGTH / 6));
}


InRoomMenu::~InRoomMenu(void)
{
}

bool	InRoomMenu::updateName(int index, Room *room, std::string *name)
{
	if (index == 0 && *name != Hud[0]->getText())
		Hud[0]->setText(*name);
	if (index > 0 && room->get_allys().size() >= index && room->get_allys().at(index - 1) != Hud[index]->getText())
		Hud[index]->setText(room->get_allys().at(index - 1));
	if (index > 0 && room->get_allys().size() < index && Hud[index]->getText() != "")
		Hud[index]->setText("");
	return (true);
}

AMenu	*InRoomMenu::onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name)
{
	if (AlignLeft)
	{
		if (selected == 0)
		{
			comhandler->SendCommand(START_GAME, std::string(""));
			return (NULL);
		}
		if (selected == 1)
		{
			comhandler->SendCommand(LEAVE_ROOM, std::string(""));
			return (new JoinRoomMenu());
		}
	}
	return (NULL);
}

AMenu	*InRoomMenu::myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name)
{
	if (updateDelta == 0)
	{
		updateDelta = 20;
		for (int i = 0; i < 4; i++)
			if (!updateName(i, room, name))
				return (this);
	}
	else
		--updateDelta;
	return (NULL);
}