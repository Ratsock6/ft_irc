/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:03:17 by mgallais          #+#    #+#             */
/*   Updated: 2024/08/02 03:20:42 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/// Constructors & Destructor :
Server::Server( const int port, std::string password )
{
	this->port = port;
	this->password = password;
	this->server_status = STOPPED;
	this->poll_size = 1;
	this->poll_count = 0;
	this->all_sockets = std::vector<struct pollfd>(max_clients);

	std::cout << BWhite;
	std::cout << "[Server] Server initialized\n";
	std::cout << Color_Off;
}

Server::~Server()
{
	
	std::cout << BWhite;
	std::cout << "[Server] Server destroyed\n";
	std::cout << Color_Off;
}
/// ---



/// Private Functions :

// Create the server socket, and bind it
void	Server::create_server_socket()
{
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
	server_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (server_socket == -1) {
		freeaddrinfo(res);
		throw std::runtime_error( strerror(errno) );
	}

	std::cout << BWhite;
	std::cout << "[Server] Created server socket fd: " << server_socket << std::endl;
	std::cout << Color_Off;

	// Binding of the socket to the address and port
	status = bind(server_socket, res->ai_addr, res->ai_addrlen);
	if (status != 0) {
		freeaddrinfo(res);
		close(server_socket);
		throw std::runtime_error( strerror(errno) );
	}

	std::cout << BWhite;
	std::cout << "[Server] Bound socket to localhost port " << port << std::endl;
	std::cout << Color_Off;

	// Listen for incoming connections
	status = listen(server_socket, 5);
	if (status != 0) {
		freeaddrinfo(res);
		close(server_socket);
		throw std::runtime_error( strerror(errno) );
	}

	// Set the server socket to non-blocking
	if (fcntl(server_socket, F_SETFL, O_NONBLOCK) == -1) 
		throw std::runtime_error("fcntl: " + std::string(strerror(errno)));

	// Add the server socket to the pollfd array
	poll_count = 1;
	all_sockets[0].fd = server_socket;
	all_sockets[0].events = POLLIN;
	all_sockets[0].revents = 0;

	std::cout << BWhite;
	std::cout << "[Server] Ready " << std::endl;
	std::cout << Color_Off;

	// Clean up
	freeaddrinfo(res);
}

Client& Server::get_client_by_socket(int client_socket)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (clients[i].getFd() == client_socket)
			return clients[i];
	}
	throw std::invalid_argument("Client does not exist");
}

int Server::new_ID()
{
	return clients.size() + 1;
}

void	Server::close_all_clients()
{
	for (int i = 1; i < poll_count; i++)
		close(all_sockets[i].fd);
	
	clients.clear();
	channels.clear();
	poll_count = 0;
}
/// ---



/// Public Functions :
void	Server::start()
{
	signal_handler();
	try
	{
		create_server_socket();
		server_status = RUNNING;
		time = std::time(NULL);
		server_loop();
	}
	catch(const std::exception& e)
	{
		std::cerr << BRed;
		std::cerr << "[Server] Critical error : " << e.what() << " | Shutdown\n";
		std::cerr << Color_Off;
		//stop();
	}
}

void	Server::stop()
{
	server_status = STOPPED;
	close_all_clients();
	close(server_socket);

	std::cout << BWhite;
	std::cout << "[Server] Server stopped\n";
	std::cout << Color_Off;
}

bool Server::server_command()
{
	static bool		first_run = true;
	static bool		program_running = true;
	std::string		buffer;

	if (!program_running)
		return program_running;

	// Set stdin to non-blocking
	if (fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("fcntl: " + std::string(strerror(errno)));
	
	std::getline(std::cin, buffer);
	std::cin.clear();
	
	if (buffer == "/start" && server_status == STOPPED)
		start();

	if (buffer == "/stop" && server_status == RUNNING)
		stop();

	if (buffer.substr(0, 5) == "/port")
	{
		if (server_status == RUNNING)
		{
			std::cerr << BRed << "[Server] Cannot change port while server is running\n" << Color_Off;
			return program_running;
		}
		if (buffer.size() < 6)
		{
			std::cerr << BRed << "[Server] Need a port number\n" << Color_Off;
			return true;
		}
		std::stringstream ss;
		unsigned short new_port;

		ss << buffer.substr(6);
		ss >> new_port;
		if (ss.fail())
			std::cerr << BRed << "[Server] Port must be a number\n" << Color_Off;
		else
		{
			port = new_port;
			std::cout << BWhite << "[Server] Port changed to " << port << std::endl << Color_Off;
		}
	}

	if (buffer == "/exit")
	{
		if (server_status == RUNNING)
			stop();
		program_running = false;
	}

	if (buffer == "/help" || first_run)
	{
		if (first_run)
			first_run = false;
			
		std::cout << BCyan;
		std::cout << "[Server] /start : start the server if not running\n";
		std::cout << "[Server] /stop : stop the server if running\n";
		std::cout << "[Server] /port <port> : change the port of the server\n";
		std::cout << "[Server] /exit : exit the program\n";
		std::cout << "[Server] /help : display this help\n";
		std::cout << Color_Off;
	}
	
	return program_running;
}
/// ---



/// Getters & Setters :
int		Server::get_status() const
{
	return server_status;
}

pollfd Server::get_server_socket() const
{
	return all_sockets[0];
}

std::vector<Client>	Server::get_clients() const
{
	return clients;
}

std::vector<Channel *>	Server::get_channels() const
{
	return channels;
}

void Server::add_channel(Channel *channel)
{
	channels.push_back(channel);
}

void Server::add_client(Client client)
{
	clients.push_back(client);
}
/// ---