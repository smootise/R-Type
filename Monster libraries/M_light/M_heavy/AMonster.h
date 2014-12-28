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
	int			_id;

public:
	AMonster(int, int, int);
	virtual ~AMonster();

	virtual void	update(float dtime, ServerMessage *message) = 0;
	virtual bool	isAlive();
	virtual void	Die();
	virtual bool	isDead();
	virtual void	setMovement(int param, float pos_x, float pos_y);
	virtual void	move(float dtime);
	virtual bool	checkCollision(int size, float posx, float posy);
	virtual void	set_alive(bool alive);
	virtual void	hitme(int degats);
	virtual int		get_health() const;
	virtual int		get_pos_x() const;
	virtual int		get_pos_y() const;
	virtual int		get_direction() const;
	virtual int		get_time() const;
	virtual int		get_type() const;
	virtual int		get_id() const;
};

