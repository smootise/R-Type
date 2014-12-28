#pragma once

//enum monster_type :
// ==> AMonster.h

enum shots_type
{
	ALLY,
	ENEMI,
};

//this one is used for monsters and shots
enum info
{
	TYPE,
	ID,
	POS_X,
	POS_Y,
};

//this one is for monsters
enum monsters
{
	DIRECTION = 4,
	HP,
};

enum shots
{
	DIR_X = 4,
	DIR_Y,
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
	double	current_cd[4];
	int		current_hp[4];

	//monsters data
	int		monsters[30][6];

	//shots data
	int		shots[100][6];

	//used client side only
	bool	has_been_read;
	bool	is_game_over;
};