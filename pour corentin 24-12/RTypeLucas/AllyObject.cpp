#include "AllyObject.hpp"


AllyObject::AllyObject(int paramId) : HeroObject()
{
	id = paramId;
}


AllyObject::~AllyObject(void)
{
}

IGameObject::State	AllyObject::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	setMovement(_recv_msg->direction[id], _recv_msg->posx[id], _recv_msg->posy[id]);
	move(clock);
	posX = (posX >= WIDTH - 99) ? WIDTH - 100 : posX;
	posY = (posY >= LENGTH - 51) ? LENGTH - 52 : posY;
	return (IGameObject::Default);
}