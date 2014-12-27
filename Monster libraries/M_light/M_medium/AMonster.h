#pragma once
#include <string>
#include <iostream>
#include "ServerMessage.h"

enum monsters_type
{
	LIGHT,
	MEDIUM,
	HEAVY,
	BOSS
};

enum	direction
{
	BotLeft = 1,
	Bot = 2,
	BotRight = 3,
	Left = 4,
	Default = 5,
	Right = 6,
	UpLeft = 7,
	Up = 8,
	UpRight = 9
};

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
	int			_type; // le type du monstre (t'occupe pas)
	int			_direction; // la direction du monstre !

public:
	AMonster(int, int);
	virtual ~AMonster();

	virtual void	update(float dtime, ServerMessage *message) = 0;
	virtual bool	isAlive();
	virtual void	Die();
	virtual bool	isDead();
	virtual void	move(float x, float y);
	virtual bool	set_alive(bool alive);
	virtual int		get_time() const;
	virtual int		get_type() const;
};

