#include "AllyObject.hpp"


AllyObject::AllyObject(int paramId)
{
	id = paramId;
	speed = 0.1f;
	setMovement(AMovingObject::Default, 0, 0);
	texture = NULL;
	inited = false;
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
	if (!texture->loadFromFile("r-typesheet42.gif", sf::IntRect(0, 0, 33, 17)))
		return false;
	spriteBase.setTexture(*texture);
	spriteBase.setColor(sf::Color(255, 255, 255, 255));
	spriteBase.setScale(3.0f, 3.0f);
	inited = true;
	return true;
}

IGameObject::State	AllyObject::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	setMovement(_recv_msg->direction[id], _recv_msg->posx[id], _recv_msg->posy[id]);
	move(clock);
	posX = (posX >= WIDTH - 99) ? WIDTH - 100 : posX;
	posY = (posY >= LENGTH - 51) ? LENGTH - 52 : posY;
	return (IGameObject::Default);
}

IGameObject::State	AllyObject::draw(sf::RenderWindow &window)
{
	spriteBase.setPosition(posX, posY);
	window.draw(spriteBase);
	return (IGameObject::Default);
}