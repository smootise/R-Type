#pragma once
#include "IGameObject.hpp"
#include "ShotEntity.hpp"
#include <vector>

class ShotsObject :
	public IGameObject
{
protected:
	bool		inited;
	std::vector<ShotEntity *>	tabShot;
	sf::Texture	*textureAlly;
	sf::Texture	*textureEnemy;
public:
	ShotsObject(void);
	~ShotsObject(void);
	virtual	bool	init();
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

