/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:26:47 by mgallais          #+#    #+#             */
/*   Updated: 2024/08/05 15:26:31 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "main.hpp"

class Channel;

class Client{
	private:
		std::string username;
		std::string realname;
		std::string nickname;
		Channel *current_channel;
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

		std::string getUsername() const;
		std::string getUsername() ;
		std::string getNickname() const;
		std::string getRealname() const;
		void setRealname(std::string realname);
		int getFd() const;
		Channel getCurrentChannel() const;
		void setCurrentChannel(Channel *channel);
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