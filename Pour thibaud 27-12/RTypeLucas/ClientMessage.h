#pragma once

enum	Direction
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

struct ClientMessage
{
	char	name[256];
	double	posx;
	double	posy;
	int		direction;
	double	current_coldown;
	bool	has_been_read;
};