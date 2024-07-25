/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:22:20 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/25 09:36:19 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::server_loop()
{
	int		status;
	int		i;

	while (server_status == RUNNING)
	{
		// Poll for events
		status = poll(all_sockets.data(), poll_count, POLL_TIMEOUT);
		if (status == -1) {
			throw std::runtime_error( strerror(errno) );
		}
		else if (status == 0) {
			std::cout << BGray << "[Server] Waiting...\n" << Color_Off;
			continue;
		}
		std::cout << BGreen << "[Server] Polling...\n" << Color_Off;
		// Check for events
		for (i = 0; i < poll_count; i++)
		{
			if (all_sockets[i].revents & POLLIN)
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

	// Close the socket
	close(client_socket);

	// Remove the client from the all_sockets list
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
	
	poll_count--;
}

void	Server::receive_data(int client_socket)
{
	static std::stringstream	message;
	char				buffer[RECV_BUFFER_SIZE];
	int					status;

	status = recv(client_socket, buffer, RECV_BUFFER_SIZE, 0);
	if (status == -1) {
		throw std::runtime_error("recv: " + std::string(strerror(errno)));
	}
	else if (status == 0) {
		close_client(client_socket);
	}
	else {
		// concatenate, then interprate the message
		message << std::string(buffer, status);
		
		// if the message is complete (ending by \r\n), interprate it
		if (message.str().size() >= 2 && message.str().substr(message.str().size() - 2) == MESSAGE_END) {
			parsing_command(message.str(), channels, get_client_by_socket(client_socket));
			message.str("");
			message.clear();
		}

		std::cout << BGreen;
		std::cout << "[Server] Received message: " << message.str() << std::endl;
		std::cout << Color_Off;
	}
}

void	Server::accept_new_client()
{
	int					client_socket;
	struct pollfd		new_socket;

	client_socket = accept(server_socket, NULL, NULL);
	if (client_socket == -1) {
		throw std::runtime_error("accept: " + std::string(strerror(errno)));
	}

	new_socket.fd = client_socket;
	new_socket.events = POLLIN;
	all_sockets.push_back(new_socket);
	poll_count++;

	std::cout << BGreen;
	std::cout << "[Server] New client connected\n";
	std::cout << Color_Off;
}