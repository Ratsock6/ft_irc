#pragma once

#include <iostream>


class Client{
	private:
		std::string username;
		int user_ID;
		int fd = -1;
		std::string ip;
		bool admin;
		bool topic_autorization = false;
	public:
		Client(std::string username, int fd, bool admin);
		~Client();
		Client(const Client &c);
		Client& operator=(const Client &c);

		std::string getUsername();
		int getFd();
		std::string getIp();
		bool getAdmin();

		void setAdmin(bool admin);
};