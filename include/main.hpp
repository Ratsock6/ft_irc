/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:55:33 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 12:27:36 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// This is the main header file, which will be included in all the source files.
/// It is used to include all the necessary libraries and classes and to define some useful macros.
#pragma once

/*###########################################################################*/
/*                              Defines & Enums                              */
/*###########################################################################*/
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

/*###########################################################################*/
/*                                  Includes                                 */
/*###########################################################################*/
// Webserv needed librairies
# if defined(__APPLE__)
#  include <sys/event.h>   // For kqueue, kevent (only on BSD systems like MacOS)
# endif

# include <unistd.h>       // For execve, dup, dup2, pipe, chdir, close, read, write, access, opendir, readdir, closedir
# include <string.h>       // For strerror
# include <errno.h>        // For errno
# include <sys/types.h>    // For socketpair, waitpid, kill, stat, open
# include <sys/socket.h>   // For socket, accept, listen, send, recv, bind, connect, getaddrinfo, freeaddrinfo, setsockopt, getsockname, getprotobyname
# include <netinet/in.h>   // For htons, htonl, ntohs, ntohl
# include <sys/select.h>   // For select
# include <poll.h>         // For poll
# include <sys/epoll.h>    // For epoll_create, epoll_ctl, epoll_wait
# include <netdb.h>        // For gai_strerror, getaddrinfo, freeaddrinfo, getprotobyname
# include <fcntl.h>        // For fcntl
# include <sys/wait.h>     // For waitpid
# include <signal.h>       // For signal
# include <sys/stat.h>     // For stat, open
# include <dirent.h>    
# include <vector>  	   // For opendir, readdir, closedir


// Custom libraries
# include "color.h"       // For color definitions

# define DAILYLIB_DEF 0	  // Defines not needed
# define DAILYLIB_C_LIB 0 // C libraries not needed
# include "dailylib.hpp"  // For custom defines and structures

/*###########################################################################*/
/*                            Structures & Classes                           */
/*###########################################################################*/
// Classes
# include "Server.hpp"
class Server;

# include "Client.hpp"
class Client;

# include "Channel.hpp"
class Channel;

// Structures

/*###########################################################################*/
/*                            Functions Prototypes                           */
/*###########################################################################*/
int connection_setup(int port, char *password);
char	**ft_split(char const *s, char c);
int parsing_command(char *str);