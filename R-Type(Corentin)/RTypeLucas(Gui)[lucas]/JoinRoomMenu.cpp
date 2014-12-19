#include "JoinRoomMenu.hpp"
#include "RoomFirstMenu.hpp"

JoinRoomMenu::JoinRoomMenu(void)
{
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
				  std::vector<std::string> *availlablerooms, Room	*room)
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
	if (inLoading == false)
		return (NULL);
	if (state["Pending"] == false)
	{
		inLoading = false;
		return (createRooms(availlablerooms));
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
				  std::vector<std::string> *availlablerooms, Room	*room)
{
	if (leftOrRight == 4)
	{
		if (selected == 0 && inLoading == false)
		{
			inLoading = true;
			comhandler->SendCommand(GET_ROOMS, new std::string(""));
			return (NULL);
		}
		if (selected == 1)
			return (new RoomFirstMenu());
	}
	return (NULL);
}