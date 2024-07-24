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
    if (command == "/kick") return KICK;
    if (command == "/invite") return INVITE;
    if (command == "/topic") return TOPIC;
    if (command == "/mode") return MODE;
    if (command == "/msg") return MSG;
    if (command == "/nick") return NICK;
    if (command == "/part") return PART;
    if (command == "/quit") return QUIT;
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

bool is_channel(std::vector<Channel> channels, std::string channel_name)
{
    channel_name.erase(0, 1);
    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (it->get_channel_name() == channel_name)
            return true;
    }
    return false;
}
int switch_search_command(std::vector<std::string> args, Channel channel, Client client)
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
            channel.send_msg_to_channel("test", client);
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
        case CMD_ERROR:
            throw std::invalid_argument("Command does not exist");
    }
    return 1;
}

Channel Search_channel(std::vector<Channel> channels, std::string channel_name)
{
    if (channel_name[0] != '#')
        throw std::invalid_argument("Channel name does not start with #");
    channel_name.erase(0, 1);
    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (it->get_channel_name() == channel_name)
            return *it;
    }
    throw std::invalid_argument("Channel does not exist");
}
int parsing_command(const std::string& str , std::vector<Channel> channels, Client client) {
    if (str[0] != '/')
        return 0;
    
    std::istringstream stream(str);
    std::vector<std::string> args;
    std::string arg;
    while (stream >> arg) {
        args.push_back(arg);
    }
    if (args.empty()) {
        throw std::invalid_argument("Empty command");
    }
    if (is_channel(channels, args[1]) == false)
        throw std::invalid_argument("Channel does not exist");
    Channel channel = Search_channel(channels, args[1]);
    args.erase(args.begin() + 1);
    switch_search_command(args, channel, client);

    return 1;
}
