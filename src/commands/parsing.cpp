#include "main.hpp"
//return value :
// 0 == no command
// 1 == command without problem
// -1 == command does not exist
// -2 == command existing but problem with

enum command
{
	KICK,
	INVITE,
	TOPIC,
	MODE,
	CMD_ERROR
};

enum mode{
	i,
	t,
	k,
	o,
	l,
	mode_error
};

int get_command(char *str)
{
	if(strcmp(str, "/kick") == 0)
		return KICK;
	if(strcmp(str, "/invite") == 0)
		return INVITE;
	if(strcmp(str, "/topic") == 0)
		return TOPIC;
	if(strcmp(str, "/mode") == 0)
		return MODE;
	return CMD_ERROR;
}
int get_mode(char *str)
{
	if(strcmp(str, "i") == 0)
		return i;
	if(strcmp(str, "t") == 0)
		return t;
	if(strcmp(str, "k") == 0)
		return k;
	if(strcmp(str, "o") == 0)
		return o;
	if(strcmp(str, "l") == 0)
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
			std::cerr << "Mode does not exist\n";
			return -1;
	}
	return 1;
}
int parsing_command(char *str)
{
	char **args;

	if(str[0] != '/')
		return 0;
	args = ft_split(str, ' ');
	for(int i = 0; args[i] != NULL; i++)
		std::cout << args[i] << std::endl;
	switch(get_command(args[0]))
	{
		case KICK:
			if(args[1] == NULL || args[2] == NULL)
				return -2;
			break;
		case INVITE:
			if(args[1] == NULL || args[2] == NULL)
				return -2;
			break;
		case TOPIC:
			if(args[1] == NULL)
				return -2;
			break;
		case MODE:
			if(args[0] == NULL || args[1] == NULL)
				return -2;
			return(parsing_mode(strdup(args[1])));
			break;
		case CMD_ERROR:
			std::cerr << "Command does not exist\n";
			return -1;
	}
	return 1;
}