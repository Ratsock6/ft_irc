/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:55:33 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/11 11:30:07 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// This is the main header file.
/// It is used to include all the necessary libraries and classes and to define some useful macros.
#pragma once

/*###########################################################################*/
/*                                   Defines                                 */
/*###########################################################################*/


/*###########################################################################*/
/*                                  Includes                                 */
/*###########################################################################*/
#include <iostream>      // For standard input/output functions (std::cout, std::cin, std::cerr)
#include <algorithm>     // For functions std::min, std::max, std::sort, std::find, std::count, std::replace, std::remove
#include <cstring>       // For string manipulation functions (strlen, strcpy, strcmp, ...)
#include <sys/types.h>   // For socket data types
#include <sys/socket.h>  // For socket functions: socket, bind, connect, listen, accept, setsockopt
#include <sys/time.h>    // For struct timeval used in select()
#include <unistd.h>      // For functions close, lseek, fstat
#include <netinet/in.h>  // For functions htons, htonl, ntohs, ntohl and data structures for addresses
#include <arpa/inet.h>   // For functions inet_addr, inet_ntoa
#include <netdb.h>       // For functions getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo
#include <csignal>       // For functions signal, sigaction
#include <fcntl.h>       // For functions fcntl
#include <poll.h>        // For function poll
#include <sys/stat.h>    // For function fstat
#include <cstdio>        // For standard input/output functions if needed (e.g. printf)
#include <cstdlib>       // For type conversion functions if needed (e.g. atoi, atof)
#include <ctime>         // For time functions (time, clock, difftime, mktime, ...)

#include "color.h"       // For color definitions
#include "dailylib.h"	 // For custom defines and structures

/*###########################################################################*/
/*                            Structures & Classes                           */
/*###########################################################################*/


/*###########################################################################*/
/*                            Functions Prototypes                           */
/*###########################################################################*/