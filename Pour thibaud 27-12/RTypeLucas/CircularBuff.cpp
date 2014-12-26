#include <string>
#include <iostream>
#include "CircularBuff.h"

CircularBuff::CircularBuff(void)
{
}


CircularBuff::~CircularBuff(void)
{
	_data.clear();
}

void				CircularBuff::add_data(Message &msg)
{
	_data.push_back(msg);
}

std::vector<Message>		&CircularBuff::get_data(void)
{
	return (_data);
}