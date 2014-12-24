#include "Message.h"

Message::Message(uint32_t rq_type, uint32_t data_length, char *packet, Client &client) :
_rq_type(rq_type), _data_length(data_length), _packet(packet),  _client(client)
{

}

Message::Message(const Message &mess) :
  _client(mess._client)
{
  this->_rq_type = mess._rq_type;
  this->_data_length = mess._data_length;
  this->_packet = mess._packet;
}

Message::~Message(void)
{

}

//setters & getters

uint32_t			Message::get_rq_type(void) const { return (_rq_type); }
uint32_t			Message::get_data_length(void) const { return (_data_length); }
char				*Message::get_packet(void) const { return (_packet); }
Client				&Message::get_client(void) const { return (_client); }

void	Message::to_string() const
{
	std::cout << "requete type :" << _rq_type << std::endl;
	std::cout << "data_length :" <<	_data_length << std::endl;
	if (_data_length != 0)
		std::cout << "paquet additonnel :" << _packet << std::endl;
}

Message		&Message::operator=(const Message &msg)
{
	this->_rq_type = msg._rq_type;
	this->_data_length = msg._data_length;
	this->_packet = msg._packet;
	this->_client = msg._client;

	return (*this);
}
