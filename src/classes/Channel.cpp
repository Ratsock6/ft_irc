#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(std::string channel_name, Client &creator)
    : channel_name(channel_name), creator(creator) {
	Channel::add_admin(creator, creator);
	invite_only = false;
	topic = "No topic is set";
	topic_autorization = true;
	user_limit = 20;
	users_list.insert(std::pair<Client, bool>(creator, true));
}

Channel::~Channel(){
}

// Channel::Channel(const Channel &c)
//     : 
// 	  user_limit(c.user_limit),
// 	  channel_name(c.channel_name),
//       password(c.password) ,
// 	  topic(c.topic),
// 	  users_list(c.users_list),
// 	  creator(c.creator),
// 	  invite_only(c.invite_only),
// 	  topic_autorization(c.topic_autorization){
//     // No need for further assignments as they are handled in the initializer list
// }

Channel& Channel::operator=(const Channel &c){
	this->channel_name = c.channel_name;
	this->topic = c.topic;
	this->users_list = c.users_list;
	this->creator = c.creator;
	this->invite_only = c.invite_only;
	this->user_limit = c.user_limit;
	this->topic_autorization = c.topic_autorization;
	this->password = c.password;
	return *this;
}

void Channel::add_user_by_admin(Client user_to_add, Client user_who_add){
	if (users_list[user_who_add] == false)
		throw std::invalid_argument("You are not an admin");
	if (users_list.find(user_to_add) == users_list.end())
		this->users_list[user_to_add] = false;
	else
		throw std::invalid_argument("User already in the channel");
}

void Channel::remove_user(Client user_to_remove, Client user_who_remove){
	if (users_list[user_who_remove] == false)
		throw std::invalid_argument("You are not an admin");
	if (user_to_remove.getID() == this->creator.getID())
		throw std::invalid_argument("You are trying to remove the creator of the channel (its the big boss)");
	if (users_list[user_to_remove] == true)
		this->users_list.erase(user_to_remove);
	else {
		throw std::invalid_argument("Try but not working");
	}
}

void Channel::add_admin(Client user_to_add, Client user_who_add){

	if (users_list[user_who_add] == true || user_who_add.getID() == this->creator.getID())
	{
		if (users_list[user_to_add] == false)
			users_list[user_to_add] = true;
		else
			throw std::invalid_argument("User already admin in this channel");
	}
	else
		throw std::invalid_argument("You are not an admin");
	// if (user_who_add.getAdmin() == true){
	// 	for (std::map<Client, bool>::iterator it = this->admin_users_list.begin(); it != this->admin_users_list.end(); it++){
	// 		if (it->first.getID() == user_to_add.getID()){
	// 			throw std::invalid_argument("User already admin in this channel");
	// 			return;
	// 		}
	// 	}
	// 	this->admin_users_list.push_back(user_to_add);
	// }
	// else{
	// 	throw std::invalid_argument("You are not an admin");
	// }
}
void Channel::remove_admin(Client user, Client admin){
	//if (admin.getAdmin() == true && user.getID() != this->creator.getID()){
	if (users_list[admin] == true){
		if (users_list[user] == true)
			users_list[user] = false;
		else
			throw std::invalid_argument("User is not an admin");
	}
	else if(user.getID() == this->creator.getID()){
		throw std::invalid_argument("you are trying to remove the creator of the channel (its the big boss)");
	}
	else{
		throw std::invalid_argument("You are not an admin");}
}

void Channel::set_password(std::string password, Client client){
	if (client.getAdmin() == true){
		std::cout << "Password set" << std::endl;
		this->password = password;
	}
}

std::string Channel::get_password(){
	return this->password;
}

void Channel::unset_password(Client client){
	if (client.getAdmin() == true){
		this->password.clear();
	}
}

void Channel::join_request(Client user_to_add, std::string password){
	std::cout << "channel pwd : "<< this->password << " user pwd :" << password << std::endl;
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
		std::cout << "User " << user_to_add.getUsername() << " joined the channel" << std::endl;
		this->users_list.insert(std::pair<Client, bool>(user_to_add, false));
	}
	else{
		throw std::invalid_argument("Wrong password 2");
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

void Channel::send_msg_to_channel(std::string msg, Client client, bool MSG_OR_OTHER){
	std::cout << "sending msg to channel " << msg << std::endl;
	std::string temp;
	if (MSG_OR_OTHER == true)
		temp = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getRealname() + " PRIVMSG " + this->channel_name + " :" + msg + "\r\n";
	else
		temp = msg;
	std::cout << temp << std::endl;
	std::cout << "user list size :" << this->users_list.size() << std::endl;
	for (std::map<Client, bool>::iterator it = this->users_list.begin(); it != this->users_list.end(); ++it) {
		if (it->first.getFd() != client.getFd())
		{
            send(it->first.getFd(), temp.c_str(), temp.size(), 0);
			std::cout << "fd: "<< it->first.getFd() << std::endl;
		}
	}
}

std::map<Client, bool> Channel::get_users_map(){
	return this->users_list;
}

void Channel::send_private_msg(std::string msg , Client who_send, Client who_receive)
{
	std::cout << "(to remove) :" << " user : " << who_send.getUsername() << " send to : " << who_receive.getUsername() << " : " << msg << std::endl;
	std::string final_msg = "user : " + who_send.getUsername() + " send you : " + msg;
	std::cout << final_msg << std::endl;
	send(who_receive.getFd(), final_msg.c_str() , final_msg.size(), 0);
}

std::string Channel::get_channel_name(){
	return this->channel_name;
}

std::string Channel::get_topic(){
	return this->topic;
}

std::vector<Client> Channel::get_users_list(){
	std::vector<Client> users_list;
	if (this->users_list.empty())
		return users_list;
	for (std::map<Client, bool>::iterator it = this->users_list.begin(); it != this->users_list.end(); it++){
		users_list.push_back(it->first);
	}
	return users_list;
}

std::vector<Client> Channel::get_admin_users_list(){
	std::vector<Client> admin_list;
	for (std::map<Client, bool>::iterator it = this->users_list.begin(); it != this->users_list.end(); it++){
		if (it->second == true){
			admin_list.push_back(it->first);
		}
	}
	return admin_list;
}

Client Channel::get_creator(){
	return this->creator;
}