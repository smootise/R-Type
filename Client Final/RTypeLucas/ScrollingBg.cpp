#include "ScrollingBg.hpp"

#include <iostream>

ScrollingBg::ScrollingBg(void)
{
	inited = false;
	speed = 0.002f;
	decal = 0.f;
	texture = NULL;
}


ScrollingBg::~ScrollingBg(void)
{
	if (texture)
		delete texture;
}

bool	ScrollingBg::init()
{
	if (inited)
		return true;
	texture = new sf::Texture();
	if (!texture->loadFromFile("Background.png"))
		return false;
	backGround1.setTexture(texture);
	backGround2.setTexture(texture);
	backGround1.setPosition(0, 0);
	backGround2.setPosition(0, 0);
	backGround1.setSize(sf::Vector2f(WIDTH, LENGTH));
	backGround2.setSize(sf::Vector2f(WIDTH, LENGTH));
	inited = true;
	return true;
}

IGameObject::State	ScrollingBg::update(sf::Event *, const sf::Clock &clock, ServerMessage *_recv_msg, ClientMessage *_send_msg)
{
	decal -= speed * clock.getElapsedTime().asMicroseconds();
	while (decal <= -1 * WIDTH)
		decal += WIDTH;
	backGround1.setPosition(decal + WIDTH, 0);
	backGround2.setPosition(decal, 0);
	return (Default);
}

IGameObject::State	ScrollingBg::draw(sf::RenderWindow &window)
{
	window.draw(backGround1);
	window.draw(backGround2);
	return (Default);
}