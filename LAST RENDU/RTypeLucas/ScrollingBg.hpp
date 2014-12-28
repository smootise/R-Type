#pragma once
#include "IGameObject.hpp"

class ScrollingBg :
	public IGameObject
{
protected:
	float	speed;
	float	decal;
	sf::RectangleShape	backGround1;
	sf::RectangleShape	backGround2;
	sf::Texture *texture;
	bool	inited;
public:
	ScrollingBg(void);
	~ScrollingBg(void);
	virtual	bool	init();
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *);
	virtual State	draw(sf::RenderWindow &);
};

