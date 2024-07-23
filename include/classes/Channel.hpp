#pragma once 

#include <iostream>
#include <vector>
#include "Client.hpp"

class channel{
	private:
		std::string channel_name;
		std::string topic;
		std::vector<Client> users;
		std::vector<Client> admin_users;
		Client creator;
	public:
		channel(std::string channel_name, Client creator);
		~channel();
		channel(const channel &c);
		channel& operator=(const channel &c);

		void add_user(Client user);
		void remove_user(Client user);
		void add_admin(Client user);
		void remove_admin(Client user);
		void change_topic(std::string topic_name, Client client);
};