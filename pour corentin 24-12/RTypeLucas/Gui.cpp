#include "Gui.hpp"
#include "BaseMenu.hpp"
#include "ScrollingBg.hpp"
#include "HeroObject.hpp"
#include "AllyObject.hpp"
Gui::Gui(void)
{
	menu = NULL;
}


Gui::~Gui(void)
{
	if (menu)
		delete menu;
}

bool	Gui::init()
{
	menu = new BaseMenu();
	window.create(sf::VideoMode(WIDTH, LENGTH), "RType");
	if (!menu->init())
		return (false);
	return (loadGame()); //a retirer
	return (true);
}

bool	Gui::loadGame()
{
	gObjects.push_back(new ScrollingBg());
	gObjects.push_back(new HeroObject());
	gObjects.push_back(new AllyObject(1));
	for (std::vector<IGameObject *>::iterator it = gObjects.begin(); it != gObjects.end(); it++)
		if (!(*it)->init())
		return (false);
	return (true);
}

Gui::State	Gui::affGame(ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	if (window.isOpen())
    {
        sf::Event event;
		bool called = false;
		bool ret;
		while ((ret = window.pollEvent(event)) || called == false)
        {
			called = true;
            if (event.type == sf::Event::Closed)
			{
                window.close();
				return (Quit);
			}
			for (std::vector<IGameObject *>::iterator it = gObjects.begin(); it != gObjects.end(); it++)
				(*it)->update((ret == true) ? &event : NULL, clock, _recv_msg, _send_msg);
        }
        window.clear();
		for (std::vector<IGameObject *>::iterator it = gObjects.begin(); it != gObjects.end(); it++)
			(*it)->draw(window);
        window.display();
		clock.restart();
    }
	else
		return (Quit);
	return (Default);
}

Gui::State	Gui::affScreen(std::map <std::string, bool>	&_state, CommandHandler	*comhandler, 
							std::vector<std::string> *_availlablerooms, Room *room, std::string *name)
{
	AMenu	*tmp;

	if (window.isOpen())
    {
        sf::Event event;
		bool called = false;
		bool ret;
		while ((ret = window.pollEvent(event)) || called == false)
        {
			called = true;
            if (event.type == sf::Event::Closed || (tmp = menu->update((ret == true) ? &event : NULL,
					_state, comhandler,	_availlablerooms, room,
					name)) == menu)
			{
                window.close();
				return (Quit);
			}
			else if (tmp)
			{
				delete (menu);
				menu = tmp;
				if (!menu->init())
					return (Error);
			}
        }
        window.clear();
		menu->draw(window);
        window.display();
		clock.restart();
    }
	else
		return (Quit);
	return (Default);
}