#include "Channel.hpp"

Channel::Channel(std::string channel_name, const Client& creator)
    : channel_name(channel_name), creator(creator) {
    Channel::add_user(creator);
	Channel::add_admin(creator);
}

Channel::~Channel(){
}

Channel::Channel(const Channel &c)
    : channel_name(c.channel_name), creator(c.creator) {
	this->topic = c.topic;
	this->users_list = c.users_list;
	this->admin_users_list = c.admin_users_list;
}

Channel& Channel::operator=(const Channel &c){
	this->channel_name = c.channel_name;
	this->topic = c.topic;
	this->users_list = c.users_list;
	this->admin_users_list = c.admin_users_list;
	this->creator = c.creator;
	return *this;
}

void Channel::add_user(Client user){
	this->users_list.push_back(user);
}

void Channel::remove_user(Client user){
	for (std::vector<Client>::iterator it = this->users_list.begin(); it != this->users_list.end(); it++){
		if (it->getID() == user.getID()){
			this->users_list.erase(it);
			break;
		}
	}
}

void Channel::add_admin(Client user){
	this->admin_users_list.push_back(user);
}

void Channel::remove_admin(Client user){
	for (std::vector<Client>::iterator it = this->admin_users_list.begin(); it != this->admin_users_list.end(); it++){
		if (it->getID() == user.getID()){
			this->admin_users_list.erase(it);
			break;
		}
	}
}

void Channel::change_topic(std::string topic_name, Client client){
	if (client.getID() == this->creator.getID()){
		this->topic = topic_name;
	}
}

std::string Channel::get_channel_name(){
	return this->channel_name;
}

std::string Channel::get_topic(){
	return this->topic;
}

std::vector<Client> Channel::get_users_list(){
	return this->users_list;
}

std::vector<Client> Channel::get_admin_users_list(){
	return this->admin_users_list;
}

Client Channel::get_creator(){
	return this->creator;
}