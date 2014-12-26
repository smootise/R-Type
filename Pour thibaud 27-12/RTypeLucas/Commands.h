#pragma once

enum Commands
{
	NONE = 0,
	LOGIN = 1,
	LOGOUT = 2,
	GET_ROOMS = 3,
	JOIN_ROOM = 4,
	LEAVE_ROOM = 5,
	CREATE_ROOM = 6,
	START_GAME = 7,
};

enum Answers
{
	OK = 10,
	NOK = 11,
	BUSY = 12,
	ADD_ALLY = 13,
	REMOVE_ALLY = 14,
	GAME_STARTED = 15,
};