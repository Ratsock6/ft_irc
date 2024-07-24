#pragma once

#include "main.hpp"

class Client{
	private:
		std::string username;
		int user_ID;
		int fd;
		std::string ip;
		bool admin;
		bool topic_autorization;
	public:
		Client(std::string username, int fd, bool admin);
		~Client();
		Client(const Client &c);
		Client& operator=(const Client &c);

		std::string getUsername();
		int getFd();
		std::string getIp();
		bool getAdmin();
		bool getTopicAutorization();
		int getID();

		void setAdmin(bool admin);
		void setTopicAutorization(bool topic_autorization);
};