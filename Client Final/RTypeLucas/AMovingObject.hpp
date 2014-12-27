#pragma once
#include "IGameObject.hpp"

class AMovingObject :
	public IGameObject
{
protected:
	enum	Direction
	{
		BotLeft = 1,
		Bot = 2,
		BotRight = 3,
		Left = 4,
		Default = 5,
		Right = 6,
		UpLeft = 7,
		Up = 8,
		UpRight = 9
	};
	float	speed;
	float	posX;
	float	posY;
	Direction	direction;
	virtual void	setMovement(int param, float startingX = -1, float startingY = -1);
	virtual void	setMovement(Direction param, float startingX = -1, float startingY = -1);
	virtual void	move(const sf::Clock &);
public:
	AMovingObject(void);
	~AMovingObject(void);
	virtual	bool	init() = 0;
	virtual State	update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *) = 0;
	virtual State	draw(sf::RenderWindow &) = 0;
};

