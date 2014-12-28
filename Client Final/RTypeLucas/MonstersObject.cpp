#include "MonstersObject.hpp"
#include <iostream>

MonstersObject::MonstersObject(void)
{
	inited = false;
	tabMob.resize(0);
}


MonstersObject::~MonstersObject(void)
{

}

bool	MonstersObject::init()
{
	if (inited)
		return true;
	MonsterEntity	*tmp;
	for (unsigned int i = 0; i < 30; i++)
	{
		tmp = new MonsterEntity(i);
		tabMob.push_back(tmp);
		if (!tabMob[i]->init())
			return (false);
	}
	inited = true;
	return true;
}

IGameObject::State	MonstersObject::update(sf::Event *event, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	for (std::vector<MonsterEntity *>::iterator it = tabMob.begin(); it != tabMob.end(); it++)
		(*it)->update(event, clock, _recv_msg, _send_msg);
	return (IGameObject::Default);
}

IGameObject::State	MonstersObject::draw(sf::RenderWindow &window)
{
	for (std::vector<MonsterEntity *>::iterator it = tabMob.begin(); it != tabMob.end(); it++)
		(*it)->draw(window);
	return (IGameObject::Default);
}