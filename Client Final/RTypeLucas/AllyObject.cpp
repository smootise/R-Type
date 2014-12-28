#include "AllyObject.hpp"
#include <iostream>

AllyObject::AllyObject(int paramId)
{
	id = paramId;
	speed = 0.005f;
	setMovement(AMovingObject::Default, 0, 0);
	texture = NULL;
	inited = false;
	toDraw = false;
}


AllyObject::~AllyObject(void)
{
	if (texture)
		delete texture;
}

bool	AllyObject::init()
{
	if (inited)
		return true;
	texture = new sf::Texture();
	if (!texture->loadFromFile("r-typesheet42custom.gif", sf::IntRect(0, id * 17, 33, 17)))
		return false;
	spriteBase.setTexture(*texture);
	spriteBase.setColor(sf::Color(255, 255, 255, 255));
	spriteBase.setScale(3.0f, 3.0f);
	inited = true;
	return true;
}

IGameObject::State	AllyObject::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	if (!toDraw)
	{
		if (_recv_msg->has_been_read)
			return (IGameObject::Default);
		std::string	tmp(_recv_msg->name[id]);
		if (tmp == "DefaultName" || tmp == "")
			return (IGameObject::Default);
		toDraw = true;
	}
	if (!_recv_msg->has_been_read)
		setMovement(_recv_msg->direction[id], _recv_msg->posx[id], _recv_msg->posy[id]);
	move(clock);
	posX = (posX >= WIDTH - 99) ? WIDTH - 100 : posX;
	posY = (posY >= LENGTH - 51) ? LENGTH - 52 : posY;
	return (IGameObject::Default);
}

IGameObject::State	AllyObject::draw(sf::RenderWindow &window)
{
	if (!toDraw)
		return (IGameObject::Default);
	spriteBase.setPosition(posX, posY);
	window.draw(spriteBase);
	return (IGameObject::Default);
}