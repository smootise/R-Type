#pragma once
#include "AMovingObject.hpp"
#include <map>

class MonstersObject :
	public AMovingObject
{
protected:
	std::map<std::string, sf::Texture>		tabTexture;
	std::map<std::string, sf::Sprite>		tabSprite;
	bool		inited;
public:
	MonstersObject(void);
	~MonstersObject(void);
	virtual	bool	init();
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

