#include "Client.h"


Client::Client(SOCKET socket, int id, int state, std::string nickname, int room) :
	_socket(socket), _id(id), _state(state), _nickname(nickname), _room(room)
{
	
}


Client::~Client()
{

}

//setters & getters

std::string		&Client::get_nickname(void) {return (_nickname); }
SOCKET			Client::get_socket(void) {return (_socket); }
int				Client::get_id(void) {return (_id); }
int				Client::get_state(void) {return (_state); }
int				Client::get_room(void) {return (_room); }

void			Client::set_nickname(std::string &nickname) { _nickname = nickname; }
void			Client::set_id(int id) { _id = id; }
void			Client::set_state(int state) { _state = state; }
void			Client::set_room(int room) { _room = room; }