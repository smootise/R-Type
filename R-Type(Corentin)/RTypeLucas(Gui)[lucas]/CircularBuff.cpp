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

std::vector<Message>		*CircularBuff::get_data(void)
{
	std::vector<Message> 	*to_ret;

	to_ret = new std::vector<Message>(_data);
	_data.clear();
	return (to_ret);
}