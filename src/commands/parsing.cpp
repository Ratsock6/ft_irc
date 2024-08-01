#include "main.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <string>

bool str_to_bool(std::string str)
{
    if (str == "true")
        return true;
    else if (str == "false")
        return false;
    throw std::invalid_argument("Invalid boolean");
    return false;
}
int get_command(const std::string& command) {
    if (command == "KICK") return KICK;
    if (command == "INVITE") return INVITE;
    if (command == "TOPIC") return TOPIC;
    if (command == "MODE") return MODE;
    if (command == "MSG") return MSG;
    if (command == "NICK") return NICK;
    if (command == "PART") return PART;
    if (command == "QUIT") return QUIT;
    if (command == "USER") return USER;
    if (command == "PING") return PING;
    if (command == "JOIN") return JOIN;
    return CMD_ERROR;
}
int get_mode(const std::string& command) {
    if (command.compare("-i") == 0)
        return minus_i;
    if (command.compare("+i") == 0)
        return plus_i;
    if (command.compare("+t") == 0)
        return plus_t;
    if (command.compare("-t") == 0)
        return minus_t;
    if (command.compare("+k") == 0)
        return plus_k;
    if (command.compare("-k") == 0)
        return minus_k;
    if (command.compare("-o") == 0)
        return minus_o;
    if (command.compare("+o") == 0)
        return plus_o;
    if (command.compare("-l") == 0)
        return minus_l;
    if (command.compare("+l") == 0)
        return plus_l;
    return mode_error;
}

Client Search_client_ID(std::string str, std::vector<Client> users_list)
{
    for (std::vector<Client>::iterator it = users_list.begin(); it != users_list.end(); ++it)
    {
        if (it->getUsername() == str)
            return *it;
    }
    throw std::invalid_argument("User does not exist");
}

Client Search_client_by_name(std::string str, std::vector<Client> users_list)
{
    for (std::vector<Client>::iterator it = users_list.begin(); it != users_list.end(); ++it)
    {
        if (it->getUsername() == str)
            return *it;
    }
    throw std::invalid_argument("User does not exist");
}

int parsing_mode(std::vector<std::string> args, Channel &channel, Client &client)
{
    std::stringstream test;
	int num;
    for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it)
    {
        std::cout << "args: " << *it << std::endl;
    }
    int mode_temp;
    for (size_t i  =0; i < args.size(); i++)
    {
        mode_temp = get_mode(args[i]);
        if (mode_temp != mode_error)
            break;
    }
	switch(mode_temp)
	{
		case minus_i:
            if (args.size() != 2)
                throw std::invalid_argument("wrong number of arguments");
            channel.set_invite_only(false, client);
			break;
        case plus_i:
            if (args.size() != 3)
                throw std::invalid_argument("wrong number of arguments");
            channel.set_invite_only(true, client);
            break;
		case minus_t:
            if (args.size() != 2)
                throw std::invalid_argument("wrong number of arguments");
            channel.change_topic_autorization(false, client);
			break;
        case plus_t:
            if (args.size() != 2)
                throw std::invalid_argument("wrong number of arguments");
            channel.change_topic_autorization(true, client);
            break;
		case plus_k:
            if (args.size() != 3)
                throw std::invalid_argument("wrong number of arguments");
            channel.set_password(args[2], client);
			break;
        case minus_k:
            if (args.size() != 2)
                throw std::invalid_argument("wrong number of arguments");
            channel.unset_password(client);
            break;
		case plus_o:
            if(args.size() != 3)
                throw std::invalid_argument("wrong number of arguments");
            channel.add_admin(Search_client_ID(args[2], channel.get_users_list()), client);
			break;
        case minus_o:
            if(args.size() != 3)
                throw std::invalid_argument("wrong number of arguments");
            channel.remove_admin(Search_client_ID(args[3], channel.get_users_list()), client);
            break;
		case minus_l:
            if(args.size() != 2)
                throw std::invalid_argument("wrong number of arguments");
            channel.change_user_limit(0, client);
			break;
        case plus_l:
            if(args.size() != 3)
                throw std::invalid_argument("Not enough arguments");
            test << args[2];
            test >> num;
            if (test.fail())
                throw std::invalid_argument("User limit must be a number");
            channel.change_user_limit(num, client);
            break;
		case mode_error:
			throw std::invalid_argument("Mode does not exist");
	}
	return 1;
}

bool is_channel(const std::vector<Channel*>& channels, const std::string& channel_name) {
    if (channel_name.empty() || channel_name[0] != '#') {
       return false;
    }

    std::string stripped_name = channel_name.substr(1); // Retire le '#'
    for (std::vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)->get_channel_name() == stripped_name) { // Déréférencement double pour accéder à l'objet Channel
            return true;
        }
    }
    return false;
}

Channel Search_channel(const std::vector<Channel*> &channels, const std::string& channel_name) {
    if (channel_name.empty() || channel_name[0] != '#') {
        Client temp_client("temp", 0, 0, false);
        Channel temp_channel("temp", temp_client);
        return temp_channel;
    }

    std::string stripped_name = channel_name.substr(1); // Retire le '#'
    for (std::vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        std::cout << "Channel name: " << (*it)->get_channel_name() << std::endl;
    }
    for (std::vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)->get_channel_name() == stripped_name) {
            return **it; // Déréférencement double pour retourner l'objet Channel
        }
    }
    throw std::invalid_argument("Channel not found");
}


int switch_search_command(std::vector<std::string> args , const std::vector<Channel*> &channels,Client &client, Server &server)
{
    Channel channel = Search_channel(channels, args[1]);
    switch (get_command(args[0])) {
        case KICK:
            if (args.size() != 3)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            channel.remove_user(Search_client_ID(args[1], channel.get_users_list()), client);
            break;
        case INVITE:
            if (args.size() != 3)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            channel.add_user_by_admin(Search_client_ID(args[2], channel.get_users_list()), client);
            break;
        case TOPIC:
            if (args.size() != 3)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            channel.change_topic(args[2], client);
            break;
        case MODE:
            if (args.size() < 3)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            return parsing_mode(args, channel, client);
        case MSG:
            if (args.size() < 4)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            channel.send_private_msg(args[3], client, Search_client_ID(args[2], channel.get_users_list()));
            break;
        case NICK:
            if (args.size() != 2)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            //FAUT GERER NICKNAME DEJA PRIS
            client.setNickname(args[1]);
            break;
        case PART:
            if (args.size() != 2)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            channel.remove_user(client, client);
            break;
        case QUIT:
            if (args.size() != 2)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            break;
        case USER:
            if (args.size() <= 3)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            client.setUsername(args[2]);
            client.setNickname(args[1]);
            break;
        case PING:
            if (args.size() != 2)
                send_RPL_message(461, server, client, channel, "Wrong number of arguments");
            
            break;
        case JOIN:
            if (args.size() < 2 || args.size() > 3)
                throw std::invalid_argument("Wrong number of arguments");
            if (args.size() == 1)
            {
                std::cout << "test" << std::endl;
                channel.join_request(client, "");
            }
            else
                channel.join_request(client, args[1]);
            break;
        case CMD_ERROR:
            channel.send_msg_to_channel(args[1], client);
    }
    return 1;
}




int parsing_command(const std::string& str, std::vector<Channel*> channels, Client &client, Server &server) {
    // Check if the command starts with '/'
    if (str.empty()) {
        throw std::invalid_argument("empty string"); // Not a valid command
    }
    if (str == "CAP LS")
    {   Client temp_client("server", 0, 0, false);
        Channel temp_channel("temp", client);
        std::ostringstream oss;
        oss << server.get_server_socket().fd;
        std::string str = oss.str();
        temp_channel.send_private_msg((":" + str + " CAP * LS :none"), temp_client ,client);
        return 0;
    }
    // Split the command into arguments
    std::istringstream stream(str);
    std::vector<std::string> args;
    std::string arg;


    while (stream >> arg) {
        args.push_back(arg);
    }

    // Check if the arguments are empty
    if (args.empty()) {
        send_RPL_message(461, server, client , Channel("temp", client), "wrong arguments");
    }
    // Check for channel name presence
    if (args.size() < 2 || args[1].empty()) {
        send_RPL_message(461, server, client , Channel("temp", client), "wrong arguments");
    }

    if (args[0] == "JOIN" || !is_channel(channels, args[1]))
    {
        Channel new_channel(args[1], client);
        server.add_channel(&new_channel);
        channels.push_back(&new_channel);
        std::cout << "new channel created" << std::endl;
    }

    // Fetch the channel
    // Output channel details
    switch_search_command(args, channels, client, server); // Pass channel as reference

    return 1; // Command parsed successfully
}

void pre_parsing(const std::string& str, std::vector<Channel*> channels, Client &client, Server &server)
{
    std::vector<std::string> commands = splitCommands(str);
    for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); ++it)
    {
        std::cout << "command: " << *it << std::endl;
        parsing_command(*it, channels, client, server);
    }
    std::cout << "client Nick : " << client.getNickname() << " client user : " << client.getUsername() << std::endl;
    std::vector<Client> users_list = server.get_clients();
    for (std::vector<Client>::iterator it = users_list.begin(); it != users_list.end(); ++it)
    {
        std::cout << "client Nick : " << it->getNickname() << " client user : " << it->getUsername() << std::endl;
    }
}
