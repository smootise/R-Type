#pragma once

#include <vector>
#include "HudTextField.hpp"
#include "HudWindow.hpp"
#include "Room.h"
#include "CommandHandler.h"

# define WIDTH (960)
# define LENGTH (540)

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
					  std::vector<std::string> *availlablerooms, Room	*room) = 0;
	virtual AMenu	*myUpdate(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room);
public:
	AMenu(void);
	~AMenu(void);

	bool	init(void);
	AMenu	*update(sf::Event *, std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room	*room);
	void	draw(sf::RenderWindow &) const;
};