#include "main.hpp"
//return value :
// 0 == no command
// 1 == command without problem
// -1 == command does not exist
// -2 == command existing but problem with
// UTILISE DES TRY/CATCH !!!!!!!!!

// y'a pas un monde ou si je fais "saidoadaosjdaosjd/kick" ca fonctionne ?
int get_command(const std::string& command) {
    if (command == "/kick") return KICK;
    if (command == "/invite") return INVITE;
    if (command == "/topic") return TOPIC;
    if (command == "/mode") return MODE;
    return CMD_ERROR;
}
int get_mode(const std::string& command) {
    if (command.compare("i") == 0)
        return i;
    if (command.compare("t") == 0)
        return t;
    if (command.compare("k") == 0)
        return k;
    if (command.compare("o") == 0)
        return o;
    if (command.compare("l") == 0)
        return l;
    return mode_error;
}

int parsing_mode(char *str)
{
	std::cout << str << std::endl;
	switch(get_mode(str))
	{
		case i:
			break;
		case t:
			break;
		case k:
			break;
		case o:
			break;
		case l:
			break;
		case mode_error:
			throw std::invalid_argument("Mode does not exist");
	}
	return 1;
}
int parsing_command(const std::string& str) {
    if (str[0] != '/')
        return 0;

    std::istringstream stream(str);
    std::vector<std::string> args;
    std::string arg;

    while (stream >> arg) {
        args.push_back(arg);
    }

    for (std::vector<std::string>::size_type i = 0; i < args.size(); ++i) {
        std::cout << args[i] << std::endl;
    }

    if (args.empty()) {
        throw std::invalid_argument("Empty command");
    }

    switch (get_command(args[0])) {
        case KICK:
            if (args.size() < 3)
                throw std::invalid_argument("Not enough arguments");
            break;
        case INVITE:
            if (args.size() < 3)
                throw std::invalid_argument("Not enough arguments");
            break;
        case TOPIC:
            if (args.size() < 2)
                throw std::invalid_argument("Not enough arguments");
            break;
        case MODE:
            if (args.size() < 2)
                throw std::invalid_argument("Not enough arguments");
            return parsing_mode(const_cast<char*>(args[1].c_str()));
        case CMD_ERROR:
            throw std::invalid_argument("Command does not exist");
    }

    return 1;
}