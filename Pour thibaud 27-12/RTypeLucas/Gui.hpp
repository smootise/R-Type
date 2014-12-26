#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "AMenu.hpp"
#include "Room.h"
#include "CommandHandler.h"
#include "IGameObject.hpp"
#include "ClientMessage.h"
#include "ServerMessage.h"

# define WIDTH (960)
# define LENGTH (540)

class Gui
{
protected:
	sf::RenderWindow window;
	AMenu	*menu;
	sf::Clock	clock;
	std::vector<IGameObject *>	gObjects;
	sf::Texture			backText;
	sf::RectangleShape	back;
public:
	enum State
	{
		Default,
		Error,
		Quit
	};
	Gui(void);
	~Gui(void);

	bool	loadGame();
	bool	init();
	State	affScreen(std::map <std::string, bool>	&state, CommandHandler	*comhandler, 
					  std::vector<std::string> *availlablerooms, Room *room, std::string *name);
	State	affGame(ServerMessage *_recv_msg, ClientMessage *_send_msg);
};

//state te donne des infos sur la state du programme :
/* state values :
Logged => if the client is logged in or not
Pending => if the client is expecting a response to a request
Playing => if the client is in game or not
*/
//comhandler te permet de lancer des commandes, tu l'utilises comme dans l'exemple que je fais (info dans commands.h)
// availlablerooms contient en string toutes les rooms availlable
// room contient des infos sur la room dans laquelle tu es, voir room.hpp
