#include "main.hpp"

std::string int_to_string(int number)
{
	std::string result;
	std::stringstream ss;
	ss << number;
	ss >> result;
	return result;
}
void send_RPL_message(int RPL_number ,Server server, Client client, Channel channel ,std::string msg_utils = "")
{
	std::string message;
	bool throww = true;
	std::string server_name = "IRC_server";
	std::string base_msg = ":" + server_name + " 001 " + client.getNickname();
	#define PONG 6
	switch(RPL_number)
	{
		case 1:
		{
			base_msg + " :Welcome to the " + server_name + " Network, " + client.getNickname() + "!" + client.getUsername() + "@" + client.getUsername() + "\r\n";
			throww = false;
			break;
		}
		case 2:
		{
			base_msg + " :Your host is " + server_name + ", running version 8.0\r\n";
			throww = false;
			break;
		}
		case 3:
		{
			std::tm* now = std::localtime(&server.time);
			base_msg + " :This server was created " + int_to_string((now->tm_year + 1900)) + "/" + int_to_string((now->tm_mon + 1)) + "/" + int_to_string(now->tm_mday) + " " + int_to_string(now->tm_hour) + ":" + int_to_string(now->tm_min) + ":" + int_to_string(now->tm_sec) + "\r\n";
			break;
		}
		case 4:
		{
			base_msg + " :There are " + int_to_string(server.get_clients().size()) + " users connected\r\n";
			throww = false;
			break;
		}
		case 5:
		{
			base_msg + " :The channels must begin with a '#'\r\nNicklen = 30\r\n";
			throww = false;
			break;
		}
		case PONG:
		{
			message = "PONG" + server_name + "\r\n";
			throww = false;
			break;
		}
		case 461:
			base_msg + msg_utils + " :Not enough parameters\r\n";
			break;
		case 462:
			base_msg + " :You may not reregister\r\n";
			break;
		case 464:
			base_msg + " :Password incorrect\r\n";
			break;
		case 431:
			base_msg + " :No nickname given\r\n";
			break;
		case 432:
			base_msg + msg_utils + " :Erroneous nickname\r\n";
			break;
		case 433:
			base_msg + msg_utils + " :Nickname is already in use\r\n";
			break;
		case 409:
			base_msg + " :No origin specified\r\n";
			break;
		case 402:
			base_msg + server_name + " :No such server\r\n";
			break;
		case 332:
			base_msg + channel.get_channel_name() + " :No topic is set\r\n";
			break;
		case 475:
			base_msg + channel.get_channel_name() + " :Cannot join channel (+k)\r\n";
			break;
		case 403:
			base_msg + msg_utils + " :No such channel\r\n";
			break;
		case 442:
			base_msg + msg_utils + " :You're not on that channel\r\n";
			break;
		case 331:
			base_msg + msg_utils + " :No topic is set\r\n";
			break;
		case 482:
			base_msg + channel.get_channel_name() + " :You're not channel operator\r\n";
			break;
		case 401:
			base_msg + msg_utils + " :No such nick/channel\r\n";
			break;
		case 341:
		{
			base_msg + " " + msg_utils + " " +channel.get_channel_name() + "\r\n";
			throww = false;
			break;
		}
		case 473:
			base_msg + channel.get_channel_name() + " :Cannot join channel (+i)\r\n";
			break;
		case 471:
			base_msg + channel.get_channel_name() + " :Cannot join channel (+l)\r\n";
			break;
		case 696:
			base_msg + msg_utils + "\r\n";
			break;
		case 525:
			base_msg + channel.get_channel_name() + " :Key is not well-formed\r\n";
			break;
		case 502:
			base_msg + " :Cant change mode for other users\r\n";
			break;
		case 472:
			base_msg + msg_utils + " :is unknown mode char to me\r\n";
			break;
	}
	if (throww ==true)
		throw std::invalid_argument(message);
	send(client.getFd(), message.c_str(), message.size(), MSG_NOSIGNAL);

}
