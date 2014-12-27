#include "MonstersObject.hpp"

MonstersObject::MonstersObject(void)
{
}


MonstersObject::~MonstersObject(void)
{

}

bool	MonstersObject::init()
{
	if (inited)
		return true;
	if (!tabTexture["Light"].loadFromFile("r-typesheet42custom.gif", sf::IntRect(0, 0, 33, 17)))
		return false;
		/*
	if (!texture->loadFromFile("r-typesheet42custom.gif", sf::IntRect(0, id * 17, 33, 17)))
		return false;
	spriteBase.setTexture(*texture);
	spriteBase.setScale(3.0f, 3.0f);
	*/
	inited = true;
	return true;
}

IGameObject::State	MonstersObject::update(sf::Event *, const sf::Clock &, ServerMessage *, ClientMessage *)
{

}

IGameObject::State	MonstersObject::draw(sf::RenderWindow &)
{

}