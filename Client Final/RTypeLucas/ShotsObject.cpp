#include "ShotsObject.hpp"
#include <iostream>

ShotsObject::ShotsObject(void)
{
	inited = false;
	tabShot.resize(0);
	textureAlly = NULL;
}


ShotsObject::~ShotsObject(void)
{
	if (textureAlly)
		delete textureAlly;
}

bool	ShotsObject::init()
{
	if (inited)
		return true;
	textureAlly = new sf::Texture();
	if (!textureAlly->loadFromFile("r-typesheet1.gif", sf::IntRect(217, 136, 48, 14)))
		return (false);
	ShotEntity	*tmp;
	for (unsigned int i = 0; i < 100; i++)
	{
		tmp = new ShotEntity(i);
		tabShot.push_back(tmp);
		if (!tabShot[i]->init(textureAlly))
			return (false);
	}
	inited = true;
	return true;
}

IGameObject::State	ShotsObject::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	for (std::vector<ShotEntity *>::iterator it = tabShot.begin(); it != tabShot.end(); it++)
		(*it)->update(event, clock, _recv_msg, _send_msg);
	return (IGameObject::Default);
}

IGameObject::State	ShotsObject::draw(sf::RenderWindow &window)
{
	for (std::vector<ShotEntity *>::iterator it = tabShot.begin(); it != tabShot.end(); it++)
		(*it)->draw(window);
	return (IGameObject::Default);
}