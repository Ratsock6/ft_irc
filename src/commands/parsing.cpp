#include "main.hpp"
//return value :
// 0 == no command
// 1 == command without problem
// -1 == command does not exist
// -2 == command existing but problem with
// UTILISE DES TRY/CATCH !!!!!!!!!

// y'a pas un monde ou si je fais "saidoadaosjdaosjd/kick" ca fonctionne ?

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

int parsing_mode(std::vector<std::string> args, Channel channel, Client client)
{
    std::stringstream test;
	int num;
	switch(get_mode(args[1]))
	{
		case minus_i:
            if (args.size() != 2)
                throw std::invalid_argument("wrong number of arguments");
            channel.set_invite_only(false, client);
			break;
        case plus_i:
            if (args.size() != 2)
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
        throw std::invalid_argument("Channel name does not start with #");
    }

    std::string stripped_name = channel_name.substr(1); // Retire le '#'
    for (std::vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)->get_channel_name() == stripped_name) { // Déréférencement double pour accéder à l'objet Channel
            return true;
        }
    }
    return false;
}
int switch_search_command(std::vector<std::string> args, Channel channel, Client client , Server server)
{
    switch (get_command(args[0])) {
        case KICK:
            if (args.size() != 2)
                throw std::invalid_argument("Wrong number of arguments");
            channel.remove_user(Search_client_ID(args[1], channel.get_users_list()), client);
            break;
        case INVITE:
            if (args.size() != 2)
                throw std::invalid_argument("Wrong number of arguments");
            channel.add_user_by_admin(Search_client_ID(args[1], channel.get_users_list()), client);
            break;
        case TOPIC:
            if (args.size() != 2)
                throw std::invalid_argument("Wrong number of arguments");
            channel.change_topic(args[1], client);
            break;
        case MODE:
            if (args.size() < 2)
                throw std::invalid_argument("Wrong number of arguments");
            return parsing_mode(args, channel, client);
        case MSG:
            if (args.size() < 3)
                throw std::invalid_argument("Wrong number of arguments");
            channel.send_msg_to_channel("test", client, server);
            break;
        case NICK:
            if (args.size() != 2)
                throw std::invalid_argument("Wrong number of arguments");
            client.setNickname(args[1]);
            break;
        case PART:
            if (args.size() != 1)
                throw std::invalid_argument("Wrong number of arguments");
            channel.remove_user(client, client);
            break;
        case QUIT:
            if (args.size() != 1)
                throw std::invalid_argument("Wrong number of arguments");
            break;
        case USER:
            if (args.size() != 3)
                throw std::invalid_argument("Wrong number of arguments");
            client.setUsername(args[2]);
            client.setNickname(args[1]);
            break;
        case PING:
            if (args.size() != 1)
                throw std::invalid_argument("Wrong number of arguments");
            std::cout << "PONG 12 ms" << std::endl << std::endl << std::endl << std::endl;
            std::cout << "nan je deconne ca marche pas" << std::endl;
            break;
        case JOIN:
            if (args.size() < 1 || args.size() > 2)
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
            channel.send_msg_to_channel(args[0], client, server);
    }
    return 1;
}

Channel Search_channel(const std::vector<Channel*> &channels, const std::string& channel_name) {
    if (channel_name.empty() || channel_name[0] != '#') {
        throw std::invalid_argument("Channel name does not start with #");
    }

    std::string stripped_name = channel_name.substr(1); // Retire le '#'
    for (std::vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)->get_channel_name() == stripped_name) {
            return **it; // Déréférencement double pour retourner l'objet Channel
        }
    }
    throw std::invalid_argument("Channel not found");
}
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <string>

int parsing_command(const std::string& str, std::vector<Channel*> channels, Client client, Server server) {
    // Check if the command starts with '/'
    if (str.empty()) {
        return 0; // Not a valid command
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
        throw std::invalid_argument("Empty command");
    }
    // Check for channel name presence
    if (args.size() < 2 || args[1].empty()) {
        throw std::invalid_argument("No channel specified");
    }

    // Check if the channel exists
    if (!is_channel(channels, args[1])) {
        throw std::invalid_argument("Channel does not exist");
    }

    // Fetch the channel
    Channel channel = Search_channel(channels, args[1]);
    if (str[0] != '/')
        channel.send_msg_to_channel(args[0], client, server);
    // Output channel details
    std::cout << "channel name: " << channel.get_channel_name() 
              << ", channel pwd: " << channel.get_password() << std::endl;

    // Remove the channel name from arguments
    args.erase(args.begin() + 1); // Remove channel name from args

    // Process the remaining command arguments
    switch_search_command(args, channel, client, server); // Pass channel as reference

    return 1; // Command parsed successfully
}

