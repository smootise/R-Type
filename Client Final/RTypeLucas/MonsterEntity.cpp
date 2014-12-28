#include "MonsterEntity.hpp"
#include <iostream>

MonsterEntity::MonsterEntity(int paramId)
{
	speed = 0.006f;
	setMovement(AMovingObject::Default, 0, 0);
	texture["Light"] = NULL;
	texture["Medium"] = NULL;
	texture["Heavy"] = NULL;
	inited = false;
	toDraw = false;
	id = paramId;
	type = -1;
}

MonsterEntity::~MonsterEntity(void)
{
	if (texture["Light"])
		delete texture["Light"];
	if (texture["Medium"])
		delete texture["Medium"];
	if (texture["Heavy"])
		delete texture["Heavy"];
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
	inited = true;
	return true;
}

IGameObject::State	MonsterEntity::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	const static int	utilX[] = {63, 114, 96, 63};
	const static int	utilY[] = {72, 94, 96, 72};
	const static float	utilSpeed[] = {0.002f, 0.001f, 0.001f, 0.005f};

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
		setMovement(_recv_msg->monsters[id][DIRECTION], _recv_msg->monsters[id][POS_X], _recv_msg->monsters[id][POS_Y]);
		type = _recv_msg->monsters[id][TYPE];
	}
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
	const static char		*util[] = {"Light", "Medium", "Heavy", "Light"};

	if (!toDraw || type < 0 || type >= sizeof(util) / sizeof(*util))
		return (IGameObject::Default);
	spriteBase[util[type]].setPosition(posX, posY);
	window.draw(spriteBase[util[type]]);
	return (IGameObject::Default);
}