#include "JoinRoomMenu.hpp"
#include "RoomFirstMenu.hpp"
#include "InRoomMenu.hpp"

JoinRoomMenu::JoinRoomMenu(void)
{
	firstTry = true;
	inLoading = false;
	leftOrRight = 4;
	Menu.push_back(new HudWindow("Rafraichir", WIDTH / 6, 27,
		WIDTH / 3, 108));
	Menu.push_back(new HudWindow("Retour", WIDTH / 6, 135,
		WIDTH / 3, 108));
}


JoinRoomMenu::~JoinRoomMenu(void)
{
}

AMenu	*JoinRoomMenu::myUpdate(sf::Event *event, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name)
{
	if (firstTry)
	{
		std::string tmp("");
		firstTry = false;
		inLoading = true;
		comhandler->SendCommand(GET_ROOMS, tmp);
		return (NULL);
	}
	if (inLoading == false)
	{
		if (event && event->type == sf::Event::KeyPressed)
		{
			int	tmp = leftOrRight;
			int	keyCode = event->key.code;
			if (keyCode == sf::Keyboard::Left)
				leftOrRight = 4;
			if (keyCode == sf::Keyboard::Right)
				leftOrRight = 6;
			if (leftOrRight != tmp)
			{
				if (Menu.size() > 0)
					Menu[selected]->setSelected(false);
				std::vector<HudWindow *>	vectTmp = Hud;
				Hud = Menu;
				Menu = vectTmp;
				selected = 0;
				if (Menu.size() > 0)
					Menu[selected]->setSelected(true);			
			}
		}
	}
	else
	{
		if (state["Pending"] == false && leftOrRight == 4)
		{
			inLoading = false;
			return (createRooms(availlablerooms));
		}
		if (state["Pending"] == false && leftOrRight == 6)
		{
			inLoading = false;
			if (room != NULL)
				return (new InRoomMenu());
			return (NULL);
		}
	}
	return (NULL);
}

AMenu	*JoinRoomMenu::createRooms(std::vector<std::string> *availlablerooms)
{
	int	decal = 27;
	if (Hud.size() > 0)
    for (std::vector<HudWindow *>::iterator it = Hud.begin() ; it != Hud.end(); ++it)
	  delete *it;
	Hud.clear();
	for (std::vector<std::string>::iterator it = availlablerooms->begin() ; it != availlablerooms->end() && decal < 513; ++it)
	{
		Hud.push_back(new HudWindow(*it, WIDTH / 2, decal,
		WIDTH / 3, 54));
			decal += 54;
	}
	if (!init())
	{
		std::cerr << "Error during SFML init" << std::endl;
		return (this);
	}
	return (NULL);
}

AMenu	*JoinRoomMenu::onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
				  std::vector<std::string> *availlablerooms, Room	*room, std::string *name)
{
	if (leftOrRight == 4)
	{
		if (selected == 0 && inLoading == false)
		{
			std::string tmp("");
			inLoading = true;
			comhandler->SendCommand(GET_ROOMS, tmp);
			return (NULL);
		}
		if (selected == 1)
			return (new RoomFirstMenu());
	}
	else
	{
		if (Menu.size() > 0)
		{
			std::string tmp(Menu[selected]->getText());
			inLoading = true;
			comhandler->SendCommand(JOIN_ROOM, tmp);
			return (NULL);
		}
	}
	return (NULL);
}