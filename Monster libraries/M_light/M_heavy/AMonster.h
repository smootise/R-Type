#pragma once
#include <string>
#include <iostream>

class AMonster
{
protected:
	int			_timing;
	int			_health;
	int			_dmg;
	float		_speed;
	float		_size;
	float		_x;
	float		_y;
	bool		_alive;
	bool		_dead;

public:
	AMonster(int);
	virtual ~AMonster();

	virtual void	update() = 0;
	virtual bool	isAlive(int time);
	virtual void	Die();
	virtual bool	isDead();
	virtual void	move(float x, float y);
	virtual void	afftiming();
};
