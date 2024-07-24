#include "Client.hpp"
/**********************Canonic form(useless)***************************/
Client::Client(std::string username, int fd, bool admin){
	this->username = username;
	this->fd = fd;
	this->admin = admin;
	this->user_ID = Server::client_count;
	Server::client_count++;
	this->topic_autorization = false;
}

Client::~Client(){
}

Client::Client(const Client &c){
	this->username = c.username;
	this->fd = c.fd;
	this->admin = c.admin;
	this->user_ID = c.user_ID;
}

Client& Client::operator=(const Client &c){
	this->username = c.username;
	this->fd = c.fd;
	this->admin = c.admin;
	return *this;
}

/************************geter & seter******************************/

std::string Client::getUsername(){
	return this->username;
}

int Client::getFd(){
	return this->fd;
}

std::string Client::getIp(){
	return this->ip;
}

bool Client::getAdmin(){
	return this->admin;
}

void Client::setAdmin(bool admin){
	this->admin = admin;
}

void Client::setTopicAutorization(bool topic_autorization){
	this->topic_autorization = topic_autorization;
}

bool Client::getTopicAutorization(){
	return this->topic_autorization;
}

int Client::getID(){
	return this->user_ID;
}