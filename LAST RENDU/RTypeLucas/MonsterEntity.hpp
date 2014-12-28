#pragma once
#include "AMovingObject.hpp"
#include <map>

class MonsterEntity :
	public AMovingObject
{
protected:
	int			id;
	std::map<std::string, sf::Sprite>	spriteBase;
	std::map<std::string, sf::Texture *>	texture;
	bool		inited;
	bool		toDraw;
	int			type;
	int			hp;
	float		hited;
public:
	MonsterEntity(int);
	~MonsterEntity(void);
	virtual	bool	init();
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

