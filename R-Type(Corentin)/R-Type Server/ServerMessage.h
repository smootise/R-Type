#pragma once

struct ServerMessage
{
	//J1
	char	nameA[256];
	double	posxA;
	double	posyA;
	int		directionA;
	//J2
	char	nameB[256];
	double	posxB;
	double	posyB;
	int		directionB;
	//J3
	char	nameC[256];
	double	posxC;
	double	posyC;
	int		directionC;
	//J4
	char	nameD[256];
	double	posxD;
	double	posyD;
	int		directionD;
	//additional data
	char	add_info[4096];
};