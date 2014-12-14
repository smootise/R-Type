#include "Client.h"
/*
Client::Client()
{
	std::cout << "c'est la merde !" << std::endl;
}
*/

Client::Client(SOCKET socket, int id, std::string nickname, std::string roomname) :
	_socket(socket), _id(id), _nickname(nickname), _roomname(roomname)
{
	
}
/*
Client::Client(const Client &other)
{
	this->_socket = other._socket;
	this->_id = other._id;
	this->_nickname = other._nickname;
	this->_roomname = other._roomname;
}
*/


Client::~Client()
{

}

//setters & getters

std::string				Client::get_nickname(void) const {return (_nickname); }
SOCKET					Client::get_socket(void) const {return (_socket); }
int						Client::get_id(void) const {return (_id); }
std::string				Client::get_room(void) const {return (_roomname); }

void			Client::set_nickname(std::string &nickname) { _nickname = nickname; }
void			Client::set_id(int id) { _id = id; }
void			Client::set_room(std::string &room) { _roomname = room; }