#pragma once
#include "AMovingObject.hpp"
#include <map>

class ShotEntity :
	public AMovingObject
{
protected:
	int			id;
	std::map<std::string, sf::Sprite>	spriteBase;
	std::map<std::string, sf::Texture *>	texture;
	bool		inited;
	bool		toDraw;
	int			type;
	float		realPosX;
	float		realPosY;
	float		vectX;
	float		vectY;
public:
	ShotEntity(int);
	~ShotEntity(void);
	virtual	bool	init();
	virtual	bool	init(sf::Texture *, sf::Texture *);
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

