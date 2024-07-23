/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:03:17 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 15:21:08 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/// Constructors & Destructor :
Server::Server( const int port )
	: 	timeout( (timeval){ 2, 0 } )
{
	this->port = port;
	this->server_status = STOPPED;
	this->poll_size = 1;
	this->poll_count = 0;
	this->all_sockets = new pollfd[max_clients];
	std::cout << BWhite;
	std::cout << "[Server] Server initialized\n";
	std::cout << Color_Off;
}

Server::~Server()
{
	delete[] all_sockets;
}
/// ---



/// Private Functions :
void	Server::create_server_socket()
{
	int		socket_fd;
	int		status;
	

	// Init of the sockaddr struct for socket creation
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;       // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP socket

	// convertion of port to string
	std::stringstream ss;
	ss << port;

	status = getaddrinfo("localhost", ss.str().c_str(), &hints, &res);
	if (status != 0) {
		throw std::runtime_error( gai_strerror(status) );
	}

	// Socket creation
	socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (socket_fd == -1) {
		freeaddrinfo(res);
		throw std::runtime_error( strerror(errno) );
	}

	std::cout << BWhite;
	std::cout << "[Server] Created server socket fd: " << socket_fd << std::endl;
	std::cout << Color_Off;

	// Binding of the socket to the address and port
	status = bind(socket_fd, res->ai_addr, res->ai_addrlen);
	if (status != 0) {
		freeaddrinfo(res);
		close(socket_fd);
		throw std::runtime_error( strerror(errno) );
	}

	std::cout << BWhite;
	std::cout << "[Server] Bound socket to localhost port " << port << std::endl;
	std::cout << Color_Off;

	// Clean up
	freeaddrinfo(res);
}
/// ---

                                     


/// Public Functions :
void	Server::start()
{
	try
	{
		create_server_socket();
		server_status = RUNNING;
		// server_loop();
	}
	catch(const std::exception& e)
	{
		std::cerr << BRed;
		std::cerr << "[Server] Critical error : " << e.what() << " | Shutdown\n";
		std::cerr << Color_Off;
	}
}

void	Server::stop()
{
	// close_all_clients();
	// close_server_socket();
}
/// ---



/// Exceptions :
/// ---