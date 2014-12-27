#include "HeroObject.hpp"

#include <iostream>

HeroObject::HeroObject(void)
{
	speed = 0.005f;
	setMovement(AMovingObject::Default, 0, 0);
}


HeroObject::~HeroObject(void)
{

}

bool	HeroObject::init()
{
	return true;
}

IGameObject::State	HeroObject::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	int				direction = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction += 4;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction += 6;
	if (direction == 0)
		direction = 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction += 3;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction -= 3;
	setMovement(direction);
	_send_msg->direction = direction;
	_send_msg->posx = posX;
	_send_msg->posy = posY;
	move(clock);
	posX = (posX >= WIDTH - 99) ? WIDTH - 100 : posX;
	posY = (posY >= LENGTH - 51) ? LENGTH - 52 : posY;
	return (IGameObject::Default);
}

IGameObject::State	HeroObject::draw(sf::RenderWindow &window)
{
	return (IGameObject::Default);
}