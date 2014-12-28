#include "stdafx.h"
#include "AMonster.h"

AMonster::AMonster(int time, int type, int id)
: _timing(time), _type(type), _id(id)
{
	_alive = false;
	_dead = false;
}

AMonster::~AMonster()
{
	
}

void	AMonster::shoot(std::vector<Shots> &shots, int *lowestshotid, float dir_x, float dir_y)
{
	Shots		newshot(*lowestshotid, ENEMI, _dmg, _x - (_size / 2), _y -(_size / 2 - 7), dir_x, dir_y);   

	(*lowestshotid)++;
	std::cout << "apres avoir crée l'objet" << std::endl;
	shots.push_back(newshot);
	std::cout << "apres avoir push back" << std::endl;
}

void	AMonster::setMovement(int param, float startingX, float startingY)
{
	direction	tab[] = { BotLeft, Bot, BotRight, Left,	Default, Right,	UpLeft,	Up,	UpRight};

	if (param <= 0 || param >= 10)
		return;
	_direction = tab[param - 1];
	if (startingX >= 0)
		_x = startingX;
	if (startingY >= 0)
		_y = startingY;
}

void	AMonster::move(float dtime)
{
	float	dist;

	dist = dtime * _speed;
	if (_direction != 5)
	{
		//std::cout << dist << ":" << clock.getElapsedTime().asMicroseconds() << std::endl;
	}
	if (_direction % 2 == 1)
		dist /= 1.4f;
	if (_direction >= 7)
		_y -= dist;
	else if (_direction <= 3)
		_y += dist;
	if (_direction % 3 == 0)
		_x += dist;
	if (_direction % 3 == 1)
		_x -= dist;
	_x = (_x < 0) ? 0 : (_x >= 960) ? 960 - 1 : _x;
	_y = (_y < 0) ? 0 : (_y >= 540) ? 540 - 1 : _y;
}

bool AMonster::checkCollision(int s, float posx, float posy)
{
	float size;

	size = (float)s;
	if (_x > posx + size)
		return (false);
	if (_y > posy + size)
		return (false);
	if (_x + _size < posx)
		return (false);
	if (_y + _size < posy)
		return (false);
	return (true);
}

void AMonster::hitme(int dps)
{
	_health -= dps;
	if (_health <= 0)
		Die();
}


void AMonster::set_alive(bool alive)
{
	_alive = alive;
}

bool AMonster::isAlive()
{
	if (_dead == false)
		return (_alive);
	return (false);
}

bool AMonster::isDead()
{
	return (_dead);
}

void	AMonster::Die()
{
	_dead = true;
	_alive = false;
}

int		AMonster::get_health() const
{
	return (_health);
}

int		AMonster::get_time() const
{
	return (_timing);
}

int		AMonster::get_type() const
{
	return (_type);
}

int		AMonster::get_pos_x() const
{
	return ((int)_x);
}

int		AMonster::get_pos_y() const
{
	return ((int)_y);
}

int		AMonster::get_direction() const
{
	return (_direction);
}

int		AMonster::get_id() const
{
	return (_id);
}