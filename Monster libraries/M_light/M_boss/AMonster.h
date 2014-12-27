#pragma once
#include <string>
#include <iostream>
#include "ServerMessage.h"

class AMonster
{
protected:
	int			_timing;
	int			_health;
	int			_dmg;
	float		_fire_rate;
	float		_speed;
	float		_size;
	float		_x;
	float		_y;
	bool		_alive;
	bool		_dead;

public:
	AMonster(int);
	virtual ~AMonster();

	virtual void	update(float dtime, ServerMessage *message) = 0;
	virtual bool	isAlive();
	virtual void	Die();
	virtual bool	isDead();
	virtual void	move(float x, float y);
	virtual bool	set_alive(bool alive);
	virtual int		get_time() const;
};

