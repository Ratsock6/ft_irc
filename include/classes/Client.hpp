/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:26:47 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/30 15:34:59 by vsoltys          ###   ########.fr       */
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
		std::stringstream	messageBuffer;
	
	public:
		Client(std::string username, int fd, int ID, bool admin);
		~Client();
		Client(const Client &c);
		Client& operator=(const Client &c);

		std::string getUsername();
		std::string getNickname();
		int getFd() const;
		std::string getIp();
		bool getAdmin();
		bool getTopicAutorization();
		int getID() const;
		std::stringstream& getMessageBuffer();

		void setAdmin(bool admin);
		void setTopicAutorization(bool topic_autorization);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setMessageBuffer(std::stringstream &message);
		bool operator<(const Client& other) const { return getID() < other.getID(); }
		bool operator==(const Client& other) const { return this->getID() == other.getID(); }
};