#pragma once

struct ClientMessage
{
	char	name[256];
	double	posx;
	double	posy;
	int		direction;
	double	current_coldown;
	bool	has_been_read;
};