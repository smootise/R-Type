#include "ShotEntity.hpp"
#include <iostream>

ShotEntity::ShotEntity(int paramId)
{
	setMovement(AMovingObject::Default, 0, 0);
	texture["Ally"] = NULL;
	inited = false;
	toDraw = false;
	id = paramId;
	type = -1;
	realPosX = 0;
	realPosY = 0;
	vectX = 0;
	vectY = 0;
}

ShotEntity::~ShotEntity(void)
{
	if (texture["Ally"])
		delete texture["Ally"];
}

bool	ShotEntity::init(sf::Texture *textureAlly)
{
	if (inited)
		return true;
	spriteBase["Ally"].setTexture(*textureAlly);
	inited = true;
	return true;
}

bool	ShotEntity::init()
{
	if (inited)
		return true;
	texture["Ally"] = new sf::Texture();
	if (!texture["Ally"]->loadFromFile("r-typesheet1.gif", sf::IntRect(217, 136, 48, 14)))
		return false;
	spriteBase["Ally"].setTexture(*texture["Ally"]);
	inited = true;
	return true;
}

IGameObject::State	ShotEntity::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	const static int	utilX[] = {48};
	const static int	utilY[] = {14};
	const static float	utilSpeed[] = {0.01f};

	if (!_recv_msg->has_been_read && _recv_msg->monsters[id][TYPE] == -1)
		toDraw = false;
	if (!toDraw)
	{
		if (_recv_msg->has_been_read || _recv_msg->monsters[id][TYPE] == -1)
			return (IGameObject::Default);
		toDraw = true;
	}
	if (!_recv_msg->has_been_read)
	{
		type = _recv_msg->shots[id][TYPE];
		realPosX = _recv_msg->shots[id][POS_X];
		realPosY = _recv_msg->shots[id][POS_Y];
		vectX = _recv_msg->shots[id][DIR_X];
		vectY = _recv_msg->shots[id][DIR_X];
	}
	realPosX += vectX * clock.getElapsedTime().asMicroseconds();
	realPosY += vectY * clock.getElapsedTime().asMicroseconds();
	setMovement(AMovingObject::Default, realPosX, realPosY);
	if (type < 0 || type >= sizeof(utilX) / sizeof(*utilX))
		return (IGameObject::Default);
	posX = (posX >= WIDTH - utilX[type]) ? WIDTH - utilX[type] : posX;
	posY = (posY >= LENGTH - utilY[type]) ? LENGTH - utilY[type] : posY;
	return (IGameObject::Default);
}

IGameObject::State	ShotEntity::draw(sf::RenderWindow &window)
{
	const static char		*util[] = {"Ally"};

	if (!toDraw || type < 0 || type >= sizeof(util) / sizeof(*util))
		return (IGameObject::Default);
	spriteBase[util[type]].setPosition(posX, posY);
	window.draw(spriteBase[util[type]]);
	return (IGameObject::Default);
}