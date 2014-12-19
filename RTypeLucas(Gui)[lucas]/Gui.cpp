#include "Gui.hpp"
#include "BaseMenu.hpp"

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
	return (true);
}

Gui::State	Gui::affScreen(std::map <std::string, bool>	&_state, CommandHandler	*comhandler, 
							std::vector<std::string> *_availlablerooms, Room	*room)
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
					_state, comhandler,
				_availlablerooms, room)) == menu)
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
    }
	return (Default);
}