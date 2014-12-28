#include "stdafx.h"
#include "Shots.h"


//vec_x => 50 droite vec_y => gauche
Shots::Shots(int id, int type, int dmg, int x, int y, float vec_x, float vec_y)
	: _id(id), _type(type), _dmg(dmg), _x(x + 50), _y(y + 26 - 7), _dir_x(vec_x), _dir_y(vec_y)
{
	if (_type == ALLY)
		_size = 14;
	else
		_size = 14;
	_alive = true;
}


Shots::~Shots()
{
}

int		Shots::get_dmg() const
{
	return (_dmg);
}


int		Shots::get_pos_x() const
{
	return ((int)_x);
}

int		Shots::get_pos_y() const
{
	return ((int)_y);
}

int		Shots::get_type() const
{
	return (_type);
}

int		Shots::get_dir_x() const
{
	return (_dir_x);
}

int		Shots::get_dir_y() const
{
	return (_dir_y);
}

int		Shots::get_id() const
{
	return (_id);
}

int		Shots::get_size() const
{
	return ((int)_size);
}

bool	Shots::is_alive() const
{
	return (_alive);
}


void	Shots::set_alive(bool alive)
{
	_alive = alive;
}

void	Shots::move(float dtime)
{
	_x += dtime * _dir_x / 1000.0f;
	_y += dtime * _dir_y / 1000.0f;

	if (_x > 960 || _x < 0 ||  _y < 0 || _y > 540)
		this->set_alive(false);
	_x = (_x < 0) ? 0 : (_x >= 960) ? 960 - 1 : _x;
	_y = (_y < 0) ? 0 : (_y >= 540) ? 540 - 1 : _y;
}