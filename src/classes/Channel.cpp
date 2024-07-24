#include "Channel.hpp"

Channel::Channel(std::string channel_name, const Client& creator)
    : channel_name(channel_name), creator(creator) {
    Channel::add_user_by_admin(creator, creator);
	Channel::add_admin(creator, creator);
	invite_only = false;
	topic_autorization = true;
	user_limit = 20;
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

void Channel::add_user_by_admin(Client user_to_add, Client user_who_add){
	if (user_who_add.getAdmin() == true ){
		for (std::vector<Client>::iterator it = this->users_list.begin(); it != this->users_list.end(); it++){
			if (it->getID() == user_to_add.getID()){
				throw std::invalid_argument("User already in the channel");
				return;
			}
		}
		this->users_list.push_back(user_to_add);
	}
	else{
		throw std::invalid_argument("You are not an admin");
	}
}

void Channel::remove_user(Client user_to_remove, Client user_who_remove){
	if (user_who_remove.getAdmin() == true || user_who_remove.getID() == user_to_remove.getID()){
		for (std::vector<Client>::iterator it = this->users_list.begin(); it != this->users_list.end(); it++){
			if (it->getID() == user_to_remove.getID()){
				this->users_list.erase(it);
				break;
			}
		}
	}
	else{
		throw std::invalid_argument("You are not an admin");
	}
}

void Channel::add_admin(Client user_to_add, Client user_who_add){
	if (user_who_add.getAdmin() == true){
		for (std::vector<Client>::iterator it = this->admin_users_list.begin(); it != this->admin_users_list.end(); it++){
			if (it->getID() == user_to_add.getID()){
				throw std::invalid_argument("User already admin in this channel");
				return;
			}
		}
		this->admin_users_list.push_back(user_to_add);
	}
	else{
		throw std::invalid_argument("You are not an admin");
	}
}

void Channel::remove_admin(Client user, Client admin){
	if (admin.getAdmin() == true && user.getID() != this->creator.getID()){
		for (std::vector<Client>::iterator it = this->admin_users_list.begin(); it != this->admin_users_list.end(); it++){
			if (it->getID() == user.getID()){
				this->admin_users_list.erase(it);
				break;
			}
		}
	}
	else if(user.getID() == this->creator.getID()){
		throw std::invalid_argument("you are trying to remove the creator of the channel (its the big boss)");
	}
	else{
		throw std::invalid_argument("You are not an admin");}
}

void Channel::set_password(std::string password, Client client){
	if (client.getAdmin() == true){
		this->password = password;
	}
}

void Channel::unset_password(Client client){
	if (client.getAdmin() == true){
		this->password.clear();
	}
}

void Channel::join_request(Client user_to_add, std::string password){
	if (this->users_list.size() == static_cast<size_t>(this->user_limit) && this->user_limit != 0){
		throw std::invalid_argument("Channel is full");
		return;
	}
	if (this->invite_only == true)
	{
		throw std::invalid_argument("This channel is invite only");
		return;
	}
	if (this->password == password || this->password.empty()){
		this->users_list.push_back(user_to_add);
	}
	else{
		throw std::invalid_argument("Wrong password");
	}
}

void Channel::change_topic(std::string topic_name, Client client){
	if (this->topic_autorization == false){
		throw std::invalid_argument("You are not allowed to change the topic(/mode t)");
		return;

	}
	if (client.getAdmin() == true){
		this->topic = topic_name;
	}
	else{
		throw std::invalid_argument("You are not an admin");
	}
}

void Channel::change_topic_autorization(bool topic_autorization, Client client){
	if (client.getAdmin() == true){
		this->topic_autorization = topic_autorization;
	}
	else{
		throw std::invalid_argument("You are not an admin");
	}
}
void Channel::set_invite_only(bool invite_only, Client client){
	if (client.getAdmin() == true){
		this->invite_only = invite_only;
	}
}

void Channel::change_user_limit(int user_limit, Client client){
	if (user_limit < 0){
		throw std::invalid_argument("User limit can't be negative");
	}
	if (client.getAdmin() == true){
		this->user_limit = user_limit;
	}
	else{
		throw std::invalid_argument("You are not an admin");
	}
}

void Channel::send_msg_to_channel(std::string msg, Client client){
	(void)client;
	(void)msg;
	for (std::vector<Client>::iterator it = this->users_list.begin(); it != this->users_list.end(); it++){
		std::cout << "replace with the send msg function" << std::endl;
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