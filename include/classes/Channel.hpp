#pragma once 

#include <iostream>
#include <vector>
#include "Client.hpp"

class Channel{
	private:
		std::string channel_name;
		std::string topic;
		std::vector<Client> users_list;
		std::vector<Client> admin_users_list;
		Client creator;
	public:
		Channel(std::string channel_name, const Client& creator);
		~Channel();
		Channel(const Channel &c);
		Channel& operator=(const Channel &c);

		void add_user(Client user);
		void remove_user(Client user);
		void add_admin(Client user);
		void remove_admin(Client user);
		void change_topic(std::string topic_name, Client client);
};