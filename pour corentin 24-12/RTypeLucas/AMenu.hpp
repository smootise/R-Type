#pragma once

#include <vector>
#include "HudTextField.hpp"
#include "HudWindow.hpp"
#include "Room.h"
#include "CommandHandler.h"

#ifndef WIDTH
# define WIDTH (960)
#endif
#ifndef LENGTH
# define LENGTH (540)
#endif

class AMenu
{
protected:
	std::vector<HudWindow *>	Hud;
	std::vector<HudWindow *>	Menu;
	HudWindow		LoadingW;
	int		selected;
	bool	inLoading;
	bool	searchForTf;

	virtual AMenu	*onEnter(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room, std::string *name) = 0;
	virtual AMenu	*myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
public:
	AMenu(void);
	~AMenu(void);

	bool	init(void);
	AMenu	*update(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room, std::string *name);
	void	draw(sf::RenderWindow &) const;
};