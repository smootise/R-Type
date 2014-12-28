#include "MonsterEntity.hpp"
#include <iostream>

MonsterEntity::MonsterEntity(int paramId)
{
	speed = 0.006f;
	setMovement(AMovingObject::Default, 0, 0);
	texture["Light"] = NULL;
	texture["Medium"] = NULL;
	texture["Heavy"] = NULL;
	texture["Boss"] = NULL;
	inited = false;
	toDraw = false;
	id = paramId;
	type = -1;
	hp = -1;
	hited = 0.f;
}

MonsterEntity::~MonsterEntity(void)
{
	if (texture["Light"])
		delete texture["Light"];
	if (texture["Medium"])
		delete texture["Medium"];
	if (texture["Heavy"])
		delete texture["Heavy"];
	if (texture["Boss"])
		delete texture["Boss"];
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
	texture["Medium"] = new sf::Texture();
	if (!texture["Medium"]->loadFromFile("r-typesheet14.gif", sf::IntRect(78, 52, 57, 47)))
		return false;
	spriteBase["Medium"].setTexture(*texture["Medium"]);
	spriteBase["Medium"].setScale(2.0f, 2.0f);
	texture["Heavy"] = new sf::Texture();
	if (!texture["Heavy"]->loadFromFile("r-typesheet7.gif", sf::IntRect(34, 34, 32, 32)))
		return false;
	spriteBase["Heavy"].setTexture(*texture["Heavy"]);
	spriteBase["Heavy"].setScale(3.0f, 3.0f);
	texture["Boss"] = new sf::Texture();
	if (!texture["Boss"]->loadFromFile("r-typesheet39.gif", sf::IntRect(34, 2, 64, 64)))
		return false;
	spriteBase["Boss"].setTexture(*texture["Boss"]);
	spriteBase["Boss"].setScale(3.0f, 3.0f);
	inited = true;
	return true;
}

IGameObject::State	MonsterEntity::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	const static int	utilX[] = {63, 114, 96, 192};
	const static int	utilY[] = {72, 94, 96, 192};
	const static float	utilSpeed[] = {0.002f, 0.001f, 0.001f, 0.001f};

	if (!_recv_msg->has_been_read && _recv_msg->monsters[id][TYPE] == -1)
	{
		toDraw = false;
		hp = -1;
		hited = 0.f;
	}
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
		if (hp > _recv_msg->monsters[id][HP])
			hited = 500000.f;
		hp = _recv_msg->monsters[id][HP];
	}
	if (hited >= 0.f)
		hited -= clock.getElapsedTime().asMicroseconds();
	move(clock);

	if (type < 0 || type >= sizeof(utilX) / sizeof(*utilX))
		return (IGameObject::Default);
	posX = (posX >= WIDTH - utilX[type]) ? WIDTH - utilX[type] : posX;
	posY = (posY >= LENGTH - utilY[type]) ? LENGTH - utilY[type] : posY;
	speed = utilSpeed[type];
	return (IGameObject::Default);
}

IGameObject::State	MonsterEntity::draw(sf::RenderWindow &window)
{
	const static char		*util[] = {"Light", "Medium", "Heavy", "Boss"};

	if (!toDraw || type < 0 || type >= sizeof(util) / sizeof(*util))
		return (IGameObject::Default);
	spriteBase[util[type]].setPosition(posX, posY);
	if (hited > 0)
		spriteBase[util[type]].setColor(sf::Color(255, 0, 0, 155));
	else
		spriteBase[util[type]].setColor(sf::Color(255, 255, 255, 255));
	window.draw(spriteBase[util[type]]);
	return (IGameObject::Default);
}