#pragma once 

#include <iostream>
#include <vector>
#include <map>
#include "main.hpp"
class Server;

class Channel{
	private:
		int user_limit;
		std::string channel_name;
		std::string password;
		std::string topic;
		std::map<Client, bool> users_list;
		Client &creator;
		bool invite_only;
		bool topic_autorization;
	public:
		Channel(std::string channel_name, Client &creator);
		~Channel();
		//Channel(const Channel &c);
		Channel& operator=(const Channel &c);

		void add_user_by_admin(Client user_to_add, Client user_who_add);
		void join_request(Client user_to_add, std::string password);
		void remove_user(Client user_to_remove, Client user_who_remove);
		void add_admin(Client user_to_add, Client user_who_add);
		void remove_admin(Client user_to_remove, Client user_who_remove);
		void change_topic(std::string topic_name, Client client);
		void change_topic_autorization(bool topic_autorization, Client client);
		void set_password(std::string password, Client client);
		void unset_password(Client client);
		void change_user_limit(int user_limit, Client client);
		void set_invite_only(bool invite_only, Client client);
		void send_msg_to_channel(std::string msg, Client client, bool MSG_OR_OTHER);
		void send_private_msg(std::string msg, Client who_send , Client who_receive);

		std::string get_channel_name();
		std::string get_topic();
		std::vector<Client> get_users_list();
		std::vector<Client> get_admin_users_list();
		Client get_creator();
		std::string get_password();
};