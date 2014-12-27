#pragma once

enum monsters_type
{
	light,
	medium,
	heavy,
	boss
};

enum shots_type
{
	ally,
	enemi,
};

//this one is used for monsters and shots
enum info
{
	type,
	id,
	pos_x,
	pos_y,
};

//this one is for monsters
enum monsters
{
	direction = 4,
	hp,
};

enum shots
{
	dir_x = 4,
	dir_y,
};


//player
enum players
{
	J1,
	J2,
	J3,
	J4,
};

struct ServerMessage
{
	//PLayers info
	char	name[4][256];
	double	posx[4];
	double	posy[4];
	int		direction[4];

	//monsters data
	int		monsters[30][6];

	//shots data
	int		shots[100][6];

	//used client side only
	bool	has_been_read;
};