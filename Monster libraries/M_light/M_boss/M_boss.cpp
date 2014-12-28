// M_bossDLL.cpp : Defines the exported functions for the DLL application.
#include "stdafx.h"
#include "M_boss.h"

M_boss::M_boss(int time, int id) : AMonster(time, BOSS, id)
{
	_speed = 0.001f;
	_health = 30;
	_dmg = 3;
	_fire_rate = 1000000;
	_size = 192;
	_walking = true;
	_shot = 0;
	_shots = 3;
	_cd = _fire_rate;
	_pos = 0;
	_tab[0][0] = 960 - (int)_size;
	_tab[1][0] = 540 - (int)_size;
	_tab[0][1] = 100;
	_tab[1][1] = 540 - (int)_size;
	_tab[0][2] = 100;
	_tab[1][2] = 50;
	_tab[0][2] = 960 - (int)_size;
	_tab[1][2] = 50;
	_x = 960 - _size;
	_y = 270 - _size / 2;
}

M_boss::~M_boss()
{
	std::cout << "Destruction of a Monster" << std::endl;
}

void M_boss::update(float dtime, ServerMessage *message, std::vector<Shots> &shots, int *lowestshotid)
{
	if (_walking == true && (_x != _tab[0][_pos] || _y != _tab[1][_pos]))
		tryMove();
	else
	{
		_pos += 1;
		if (_pos == 4)
			_pos = 0;
		_walking = false;
		_direction = Default;
	}
	if (_walking == false)
		tryShoot(dtime, shots, lowestshotid);
	move(dtime);
}

void M_boss::tryShoot(float dtime, std::vector<Shots> &shots, int *lowestshotid)
{
	if (_cd <= 0)
	{
		this->shoot(shots, lowestshotid, -1, 0); // vers la gauche 
		_shot += 1;
		if (_shot == _shots)
		{
			_walking = true;
			_shot = 0;
		}
		_cd = _fire_rate;
	}
	else
		_cd = _cd - dtime;
}

void M_boss::tryMove()
{
	if (_tab[0][_pos] > _x)
		_direction = Bot;
	else if (_tab[0][_pos] < _x)
		_direction = Up;
	else if (_tab[1][_pos] > _y)
		_direction = Right;
	else if (_tab[1][_pos] < _y)
		_direction = Left;
}

extern "C"
{
	__declspec(dllexport) M_boss			*create(int time, int id)
	{
		M_boss		*ret = NULL;

		ret = new M_boss(time, id);
		return (ret);
	}
}