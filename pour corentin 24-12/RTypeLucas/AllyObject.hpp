#pragma once
#include "HeroObject.hpp"

class AllyObject :
	public HeroObject
{
protected:
	int	id;
public:
	AllyObject(int);
	~AllyObject(void);
	IGameObject::State	AllyObject::update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
};
