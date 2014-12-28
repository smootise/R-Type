#pragma once
#include "IGameObject.hpp"
#include "MonsterEntity.hpp"
#include <vector>

class MonstersObject :
	public IGameObject
{
protected:
	bool		inited;
	std::vector<MonsterEntity *>	tabMob;
public:
	MonstersObject(void);
	~MonstersObject(void);
	virtual	bool	init();
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

