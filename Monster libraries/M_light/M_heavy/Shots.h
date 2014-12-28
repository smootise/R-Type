#pragma once

#include "ServerMessage.h"

class Shots
{
protected:
	int			_dmg;
	float		_speed;
	float		_size;
	float		_x;
	float		_y;
	bool		_alive;
	int			_id;
	int			_type;
	float		_dir_x;
	float		_dir_y;

public:
	Shots(int id, int type, int dmg, int x, int y, float vec_x, float vec_y);
	virtual ~Shots();

	//setters and getters
	int		get_dmg() const;
	int		get_pos_x() const;
	int		get_pos_y() const;
	int		get_type() const;
	int		get_dir_x() const;
	int		get_dir_y() const;
	int		get_id() const;
	int		get_size() const;
	bool	is_alive() const;
	void	move(float);

	void	set_alive(bool alive);
};

