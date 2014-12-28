#pragma once
#include "ClientMessage.h"
#include "ServerMessage.h"
#include <SFML/Graphics.hpp>

#ifndef WIDTH
# define WIDTH (960)
#endif
#ifndef LENGTH
# define LENGTH (540)
#endif

class IGameObject
{
public:
	enum State
	{
		Default,
		Delete,
		Error
	};
	IGameObject(void) {}
	~IGameObject(void) {}
	virtual	bool	init() = 0;
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *) = 0;
	virtual State	draw(sf::RenderWindow &) = 0;
};

