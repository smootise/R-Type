#pragma once
#include "AMovingObject.hpp"

class HeroObject :
	public AMovingObject
{
protected:
	sf::Sprite	spriteBase;
	sf::Texture	*texture;
	bool		inited;
public:
	HeroObject(void);
	~HeroObject(void);
	virtual	bool	init();
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

