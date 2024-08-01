#include "main.hpp"

std::string int_to_string(int number)
{
	std::string result;
	std::stringstream ss;
	ss << number;
	ss >> result;
	return result;
}
void send_RPL_message(int RPL_number ,Server server, Client client, Channel channel)
{
	std::string message;
	std::string server_name = "IRC_server";
	#define PONG 6
	(void)channel;
	switch(RPL_number)
	{
		case 1:
			message = ":" + server_name + " 001 " + client.getNickname() + " :Welcome to the " + server_name + " Network, " + client.getNickname() + "!" + client.getUsername() + "@" + client.getUsername() + "\r\n";
			break; 
		case 2:
			message = ":" + server_name + " 002 " + client.getNickname() + " :Your host is " + server_name + ", running version 8.0\r\n";
			break;
		case 3:
		{
			std::tm* now = std::localtime(&server.time);
			message = ":" + server_name + " 003 " + client.getNickname() + " :This server was created " + int_to_string((now->tm_year + 1900)) + "/" + int_to_string((now->tm_mon + 1)) + "/" + int_to_string(now->tm_mday) + " " + int_to_string(now->tm_hour) + ":" + int_to_string(now->tm_min) + ":" + int_to_string(now->tm_sec) + "\r\n";
			break;
		}
		case 4:
			message = ":" + server_name + " 004 " + client.getNickname() + " :There are " + int_to_string(server.get_clients().size()) + " users connected\r\n";
			break;
		case 5:
			message = ":" + server_name + " 005 " + client.getNickname() + " :The channels must begin with a '#'\r\nNicklen = 30\r\n";
			break;
		case PONG:
			message = "PONG" + server_name + "\r\n";
			break;
	}
	send(client.getFd(), message.c_str(), message.size(), MSG_NOSIGNAL);

}