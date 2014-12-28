#include "AMovingObject.hpp"

#include <iostream>

AMovingObject::AMovingObject(void)
{
}

AMovingObject::~AMovingObject(void)
{
}

void	AMovingObject::setMovement(int param, float startingX, float startingY)
{
	Direction	tab[] = { BotLeft, Bot, BotRight, Left,	Default, Right,	UpLeft,	Up,	UpRight};

	if (param <= 0 || param >= 10)
		return;
	direction = tab[param - 1];
	if (startingX >= 0)
		posX = startingX;
	if (startingY >= 0)
		posY = startingY;
}

void	AMovingObject::setMovement(Direction param, float startingX, float startingY)
{
	direction = param;
	if (startingX >= 0)
		posX = startingX;
	if (startingY >= 0)
		posY = startingY;
}

void	AMovingObject::move(const sf::Clock &clock)
{
	float	dist;

	dist = clock.getElapsedTime().asMicroseconds() * speed;
	if (direction % 2 == 1)
		dist /= 1.4f;
	if (direction >= 7)
		posY -= dist;
	else if (direction <= 3)
		posY += dist;
	if (direction % 3 == 0)
		posX += dist;
	if (direction % 3 == 1)
		posX -= dist;
	posX = (posX < 0) ? 0 : (posX >= WIDTH) ? WIDTH - 1 : posX;
	posY = (posY < 0) ? 0 : (posY >= LENGTH) ? LENGTH - 1 : posY;
}