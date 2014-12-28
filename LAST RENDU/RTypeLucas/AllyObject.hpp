#pragma once
#include "AMovingObject.hpp"

class AllyObject :
	public AMovingObject
{
protected:
	int	id;
	sf::Sprite	spriteBase;
	sf::Texture	*texture;
	bool		inited;
	bool		toDraw;
	int			hp;
public:
	AllyObject(int);
	~AllyObject(void);
	virtual	bool	init();
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

