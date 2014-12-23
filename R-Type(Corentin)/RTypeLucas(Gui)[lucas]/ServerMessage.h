#pragma once

enum
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

	//additional data
	char	add_info[4096];
};