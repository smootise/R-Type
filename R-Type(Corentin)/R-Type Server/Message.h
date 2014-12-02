#pragma once
#include <stdint.h>
#include <string>
#include <iostream>

#include "Client.h"

class Message
{
protected:
	uint32_t	_rq_type;
	uint32_t	_data_length;
	void		*_packet;

	Client		&_client;

public:
	Message(uint32_t rq_type, uint32_t data_length, void *packet, Client &client);
	virtual ~Message(void);

	//setters & getters
	uint32_t	get_rq_type(void) const;
	uint32_t	get_data_length(void) const;
	void		*get_packet(void) const;
	Client		&get_client(void) const;

	//utilitaire
	void	to_string() const;
	Message	&operator=(const Message &msg);
};