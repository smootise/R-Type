#include "ShotEntity.hpp"
#include <iostream>

ShotEntity::ShotEntity(int paramId)
{
	setMovement(AMovingObject::Default, 0, 0);
	texture["Ally"] = NULL;
	texture["Enemy"] = NULL;
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
	if (texture["Enemy"])
		delete texture["Enemy"];
}

bool	ShotEntity::init(sf::Texture *textureAlly, sf::Texture *textureEnemy)
{
	if (inited)
		return true;
	spriteBase["Ally"].setTexture(*textureAlly);
	spriteBase["Enemy"].setTexture(*textureEnemy);
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
	texture["Enemy"] = new sf::Texture();
	if (!texture["Enemy"]->loadFromFile("r-typesheet1.gif", sf::IntRect(243, 277, 12, 10)))
		return false;
	spriteBase["Enemy"].setTexture(*texture["Enemy"]);
	inited = true;
	return true;
}

IGameObject::State	ShotEntity::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	const static int	utilX[] = {48, 12};
	const static int	utilY[] = {14, 10};
	const static float	utilSpeed[] = {0.01f, 0.01f};

	if (!_recv_msg->has_been_read && _recv_msg->shots[id][TYPE] == -1)
		toDraw = false;
	if (!toDraw)
	{
		if (_recv_msg->has_been_read || _recv_msg->shots[id][TYPE] == -1)
			return (IGameObject::Default);
		toDraw = true;
	}
	if (!_recv_msg->has_been_read)
	{
		type = _recv_msg->shots[id][TYPE];
		realPosX = _recv_msg->shots[id][POS_X];
		realPosY = _recv_msg->shots[id][POS_Y];
		vectX = _recv_msg->shots[id][DIR_X];
		vectY = _recv_msg->shots[id][DIR_Y];
	}
	realPosX += vectX / 1000.f * clock.getElapsedTime().asMicroseconds();
	realPosY += vectY / 1000.f * clock.getElapsedTime().asMicroseconds();
	setMovement(AMovingObject::Default, realPosX, realPosY);
	if (type < 0 || type >= sizeof(utilX) / sizeof(*utilX))
		return (IGameObject::Default);
	posX = (posX >= WIDTH - utilX[type]) ? WIDTH - utilX[type] : posX;
	posY = (posY >= LENGTH - utilY[type]) ? LENGTH - utilY[type] : posY;
	return (IGameObject::Default);
}

IGameObject::State	ShotEntity::draw(sf::RenderWindow &window)
{
	const static char		*util[] = {"Ally", "Enemy"};

	if (!toDraw || type < 0 || type >= sizeof(util) / sizeof(*util))
		return (IGameObject::Default);
	spriteBase[util[type]].setPosition(posX, posY);
	window.draw(spriteBase[util[type]]);
	return (IGameObject::Default);
}