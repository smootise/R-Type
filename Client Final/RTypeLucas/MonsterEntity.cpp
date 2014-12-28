#include "MonsterEntity.hpp"
#include <iostream>

MonsterEntity::MonsterEntity(int paramId)
{
	speed = 0.005f;
	setMovement(AMovingObject::Default, 0, 0);
	texture["Light"] = NULL;
	inited = false;
	toDraw = false;
	id = paramId;
}

MonsterEntity::~MonsterEntity(void)
{
	if (texture["Light"])
		delete texture["Light"];
}

bool	MonsterEntity::init()
{
	if (inited)
		return true;
	texture["Light"] = new sf::Texture();
	if (!texture["Light"]->loadFromFile("r-typesheet5.gif", sf::IntRect(5, 6, 21, 24)))
		return false;
	spriteBase["Light"].setTexture(*texture["Light"]);
	spriteBase["Light"].setScale(3.0f, 3.0f);
	inited = true;
	return true;
}

IGameObject::State	MonsterEntity::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	if (!toDraw)
	{
		if (_recv_msg->has_been_read || _recv_msg->monsters[id][TYPE] == -1)
			return (IGameObject::Default);
		toDraw = true;
	}
	if (!_recv_msg->has_been_read)
	{
		setMovement(_recv_msg->monsters[id][DIRECTION], _recv_msg->monsters[id][POS_X], _recv_msg->monsters[id][POS_Y]);
		type = _recv_msg->monsters[id][TYPE];
	}
	move(clock);
	posX = (posX >= WIDTH - 99) ? WIDTH - 63 : posX;
	posY = (posY >= LENGTH - 51) ? LENGTH - 72 : posY;
	return (IGameObject::Default);
}

IGameObject::State	MonsterEntity::draw(sf::RenderWindow &window)
{
	const static char		*util[] = {"Light", "Light", "Light", "Light"};

	if (!toDraw || type < 0 || type >= sizeof(util) / sizeof(*util))
		return (IGameObject::Default);
	spriteBase[util[type]].setPosition(posX, posY);
	window.draw(spriteBase[util[type]]);
	return (IGameObject::Default);
}