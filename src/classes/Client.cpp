#include "Client.hpp"
/**********************Canonic form(useless)***************************/
Client::Client(std::string username, int fd,int ID, bool admin){
	this->username = username;
	this->fd = fd;
	this->admin = admin;
	this->user_ID = ID;
	this->topic_autorization = false;
}

Client::~Client(){
}

Client::Client(const Client &c){
	this->username = c.username;
	this->nickname = c.nickname;
	this->ip = c.ip;
	this->topic_autorization = c.topic_autorization;
	this->messageBuffer.str(c.messageBuffer.str());
	this->fd = c.fd;
	this->admin = c.admin;
	this->user_ID = c.user_ID;
	this->current_channel = c.current_channel;
}

Client& Client::operator=(const Client &c){
	this->username = c.username;
	this->nickname = c.nickname;
	this->ip = c.ip;
	this->topic_autorization = c.topic_autorization;
	this->messageBuffer.str(c.messageBuffer.str());
	this->fd = c.fd;
	this->admin = c.admin;
	this->user_ID = c.user_ID;
	this->current_channel = c.current_channel;
	return *this;
}

/************************geter & seter******************************/

std::string Client::getUsername() const{
	return this->username;
}

std::string Client::getNickname() const{
	return this->nickname;
}

Channel Client::getCurrentChannel() const{
	if (this->current_channel == NULL)
		throw std::runtime_error("Client is not in a channel");
	return *this->current_channel;
}

void Client::setCurrentChannel(Channel *channel){
	this->current_channel = channel;
}

void Client::setNickname(std::string nickname){
	this->nickname = nickname;
}

void Client::setUsername(std::string username){
	this->username = username;
}

int Client::getFd() const{
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

int Client::getID() const{
	return this->user_ID;
}

std::stringstream& Client::getMessageBuffer(){
	return this->messageBuffer;
}

void Client::setMessageBuffer(std::stringstream& message){
	this->messageBuffer.str(message.str());
}