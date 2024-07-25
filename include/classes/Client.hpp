/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:26:47 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/25 11:06:39 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "main.hpp"

class Client{
	private:
		std::string username;
		std::string nickname;
		int user_ID;
		int fd;
		std::string ip;
		bool admin;
		bool topic_autorization;
		std::stringstream	messageBuffer; // used for recv
	
	public:
		Client(std::string username, int fd, int ID, bool admin);
		~Client();
		Client(const Client &c);
		Client& operator=(const Client &c);

		std::string getUsername();
		std::string getNickname();
		int getFd();
		std::string getIp();
		bool getAdmin();
		bool getTopicAutorization();
		int getID();
		std::stringstream& getMessageBuffer();

		void setAdmin(bool admin);
		void setTopicAutorization(bool topic_autorization);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setMessageBuffer(std::stringstream &message);
};