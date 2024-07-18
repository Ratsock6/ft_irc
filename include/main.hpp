/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:55:33 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/18 14:33:24 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// This is the main header file, which will be included in all the source files.
/// It is used to include all the necessary libraries and classes and to define some useful macros.
#pragma once

/*###########################################################################*/
/*                                   Defines                                 */
/*###########################################################################*/


/*###########################################################################*/
/*                                  Includes                                 */
/*###########################################################################*/
// IRC needed libraries
# include <sys/types.h>   // For socket data types
# include <sys/socket.h>  // For socket functions: socket, bind, connect, listen, accept, setsockopt
# include <sys/time.h>    // For struct timeval used in select()
# include <netinet/in.h>  // For functions htons, htonl, ntohs, ntohl and data structures for addresses
# include <arpa/inet.h>   // For functions inet_addr, inet_ntoa
# include <netdb.h>       // For functions getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo
# include <fcntl.h>       // For functions fcntl
# include <poll.h>        // For function poll
# include <sys/stat.h>    // For function fstat

// Custom libraries
# include "color.h"       // For color definitions

# define DAILYLIB_DEF 0	 // Defines not needed
# include "dailylib.h"	 // For custom defines and structures

/*###########################################################################*/
/*                            Structures & Classes                           */
/*###########################################################################*/
// Classes
# include "Server.hpp"
# include "Client.hpp"

// Structures

/*###########################################################################*/
/*                            Functions Prototypes                           */
/*###########################################################################*/