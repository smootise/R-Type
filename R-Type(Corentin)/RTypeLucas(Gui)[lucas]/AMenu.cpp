#include "AMenu.hpp"


AMenu::AMenu(void) : LoadingW("Waiting for server...", 0, 0, WIDTH / 3, 54)
{
	inLoading = false;
	selected = 0;
	Menu.resize(0);
	Hud.resize(0);
}


AMenu::~AMenu(void)
{
	if (Menu.size() > 0)
  for (std::vector<HudWindow *>::iterator it = Menu.begin() ; it != Menu.end(); ++it)
	  delete *it;
  if (Hud.size() > 0)
    for (std::vector<HudWindow *>::iterator it = Hud.begin() ; it != Hud.end(); ++it)
	  delete *it;
}

bool	AMenu::init(void)
{
	if (!LoadingW.init())
		return (false);
	searchForTf = false;
	if (Menu.size() > 0)
	for (std::vector<HudWindow *>::iterator it = Menu.begin() ; it != Menu.end(); ++it)
	  if (!(*it)->init())
		  return (false);
	if (Hud.size() > 0)
    for (std::vector<HudWindow *>::iterator it = Hud.begin() ; it != Hud.end(); ++it)
	{
	  if (!(*it)->init())
		  return (false);
		if ((*it)->getType() == HudWindow::TextField)
			searchForTf = true;
	}
	if (Menu.size() > 0)
		Menu[selected]->setSelected(true);
	return (true);
}

AMenu	*AMenu::update(sf::Event *event, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room)
{
	if (event)
	{
	if (Menu.size() > 0 && Menu[selected]->getType() == HudWindow::TextField)
	{
		HudTextField	*ptr;
		if (ptr = dynamic_cast<HudTextField *>(Menu[selected]))
			ptr->updateField(*event);
	}
	if (searchForTf)
	for (std::vector<HudWindow *>::iterator it = Hud.begin() ; it != Hud.end(); ++it)
		if ((*it)->getType() == HudWindow::TextField)
		{
			HudTextField	*ptr;
			if (ptr = dynamic_cast<HudTextField *>(Menu[selected]))
				ptr->updateField(*event);
		}
	}
	if (event && event->type == sf::Event::KeyPressed)
	{
		int	keyCode = event->key.code;
		int memSelect = selected;
		if (keyCode == sf::Keyboard::Down)
			selected += 1;
		if (keyCode == sf::Keyboard::Up)
			selected = (selected > 0) ? selected - 1 : (Menu.size() - 1 >= 0) ? Menu.size() - 1 : 0;
		if (selected > Menu.size() - 1)
			selected = 0;
		if (Menu.size() > 0 && selected != memSelect)
		{
			Menu[memSelect]->setSelected(false);
			Menu[selected]->setSelected(true);
		}
		if (keyCode == sf::Keyboard::Return)
			return (onEnter(state, comhandler, availlablerooms, room));
	}
	return (myUpdate(event, state, comhandler, availlablerooms, room));
}

void	AMenu::draw(sf::RenderWindow &app) const
{
	if (Menu.size() > 0)
	for (std::vector<HudWindow *>::const_iterator it = Menu.begin() ; it != Menu.end(); ++it)
		(*it)->draw(app);
	if (Hud.size() > 0)
	for (std::vector<HudWindow *>::const_iterator it = Hud.begin() ; it != Hud.end(); ++it)
		(*it)->draw(app);
	if (inLoading)
		LoadingW.draw(app);
}

AMenu	*AMenu::myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room)
{
	return (NULL);
}