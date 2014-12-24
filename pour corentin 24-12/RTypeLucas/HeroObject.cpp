#include "HeroObject.hpp"

#include <iostream>

HeroObject::HeroObject(void)
{
	speed = 0.0005f;
	setMovement(AMovingObject::Default, 0, 0);
	texture = NULL;
	inited = false;
}


HeroObject::~HeroObject(void)
{
	if (texture)
		delete texture;
}

bool	HeroObject::init()
{
	if (inited)
		return true;
	texture = new sf::Texture();
	if (!texture->loadFromFile("r-typesheet42.gif", sf::IntRect(0, 0, 33, 17)))
		return false;
	spriteBase.setTexture(*texture);
	spriteBase.setColor(sf::Color(255, 255, 255, 255));
	spriteBase.setScale(3.0f, 3.0f);
	inited = true;
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
	move(clock);
	posX = (posX >= WIDTH - 99) ? WIDTH - 100 : posX;
	posY = (posY >= LENGTH - 51) ? LENGTH - 52 : posY;
	_send_msg->direction = direction;
	_send_msg->posx = posX;
	_send_msg->posy = posY;
	return (IGameObject::Default);
}

IGameObject::State	HeroObject::draw(sf::RenderWindow &window)
{
	spriteBase.setPosition(posX, posY);
	window.draw(spriteBase);
	return (IGameObject::Default);
}