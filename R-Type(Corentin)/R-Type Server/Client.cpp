#include "Client.h"

Client::Client(SOCKET socket, int id, std::string nickname, std::string roomname) :
	_socket(socket), _id(id), _nickname(nickname), _roomname(roomname)
{
	
}


Client::~Client()
{

}

//setters & getters

std::string				Client::get_nickname(void) const {return (_nickname); }
SOCKET					Client::get_socket(void) const {return (_socket); }
int						Client::get_id(void) const {return (_id); }
std::string				Client::get_room(void) const {return (_roomname); }

void					Client::set_nickname(std::string &nickname) { _nickname = nickname; }
void					Client::set_id(int id) { _id = id; }
void					Client::set_room(std::string &room) { _roomname = room; }