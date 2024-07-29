/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:22:20 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/29 18:27:58 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::server_loop()
{
	int		status;

	while (server_status == RUNNING)
	{
		server_command();

		// Poll for events
		status = poll(all_sockets.data(), poll_count, POLL_TIMEOUT);
		if (status == ERROR)
			throw std::runtime_error( strerror(errno) );
		else if (status == NOTHING)
			continue;

		// Check for events
		for (int i = 0; i < poll_count; i++)
		{
			if ((all_sockets[i].revents & POLLIN) == 1)
			{
				if (all_sockets[i].fd == server_socket)
					accept_new_client();
				else
					receive_data(all_sockets[i].fd);
			}
		}
	}
}

void	Server::close_client( int client_socket )
{
	std::vector<struct pollfd>::iterator	it;
	std::vector<Client>::iterator			client_it;

	close(client_socket);

	it = all_sockets.begin();
	while (it != all_sockets.end())
	{
		if (it->fd == client_socket)
		{
			it = all_sockets.erase(it);
			break ;
		}
		else
			it++;
	}
	
	// Remove the client from the client vector
	client_it = clients.begin();
	while (client_it != clients.end())
	{
		if (client_it->getFd() == client_socket)
		{
			client_it = clients.erase(client_it);
			break ;
		}
		else
			client_it++;
	}

	if (it == all_sockets.end() || client_it == clients.end())
		throw std::runtime_error("Client not found in the list");
	
	std::cout << BGreen;
	std::cout << "[Server] Client disconnected : " << client_socket << "\n";
	std::cout << Color_Off;

	poll_count--;
}

void	Server::receive_data(int client_socket)
{
	Client				client = get_client_by_socket(client_socket);
	std::stringstream	message;
	char				buffer[RECV_BUFFER_SIZE];
	int					bytes_read;

	bytes_read = recv(client_socket, buffer, RECV_BUFFER_SIZE, 0);
	if (bytes_read < 0)
		throw std::runtime_error("recv: " + std::string(strerror(errno)));
	if (bytes_read == 0)
		close_client(client_socket);

	message << std::string(buffer, bytes_read);
		
	if (message.str().size() >= 2 && message.str().substr(message.str().size() - 2) == MESSAGE_END) {
		parsing_command(message.str(), channels, get_client_by_socket(client_socket));
	}

	std::cout << BGreen;
	std::cout << "[Server] Received message: " << message.str() << std::endl;
	std::cout << Color_Off;

	message.str("");
	message.clear();
}

void	Server::accept_new_client()
{
	int					client_socket;
	struct pollfd		new_socket;

	client_socket = accept(server_socket, NULL, NULL);
	if (client_socket == -1) {
		if (errno == EWOULDBLOCK || errno == EAGAIN) {
			return ;
		} else {
			throw std::runtime_error("accept: " + std::string(strerror(errno)));
		}
	}

	// Set the client socket to non-blocking mode
	int flags = fcntl(client_socket, F_GETFL, 0);
	if (flags == -1)
		throw std::runtime_error("fcntl: " + std::string(strerror(errno)));
	if (fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("fcntl: " + std::string(strerror(errno)));
	
	// Handle the new client connection
	if (poll_count >= max_clients)
	{
		std::cout << BRed;
		std::cout << "[Server] Too many clients connected\n";
		std::cout << Color_Off;
		close(client_socket);
		return ;
	}

	// Check if the client is already connected
	for (std::vector<pollfd>::iterator it = all_sockets.begin(); it != all_sockets.end(); ++it)
	{
		if (it->fd == client_socket)
			return;
	}

	new_socket.fd = client_socket;
	new_socket.events = POLLIN;
	all_sockets.push_back(new_socket);
	poll_count++;
	
	std::cout << BGreen;
	std::cout << "[Server] New client connected : " << client_socket << "\n";
	std::cout << Color_Off;
}