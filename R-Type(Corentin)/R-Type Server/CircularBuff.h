#pragma once
#include <vector>
#include "Message.h"

class CircularBuff
{
protected:
	std::vector<Message>	_data;

public:
	CircularBuff(void);
	virtual ~CircularBuff(void);

void						add_data(Message &msg);
std::vector<Message>		*get_data();
};

