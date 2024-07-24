/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:22:20 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/24 14:58:26 by mgallais         ###   ########.fr       */
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
		status = poll(all_sockets, poll_count, timeout.tv_sec * 1000);
		if (status == -1) {
			throw std::runtime_error( strerror(errno) );
		}
		else if (status == 0) {
			std::cout << BGray << "\r[Server] Waiting...\n" << Color_Off;
			continue;
		}

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

	std::cout << BWhite;
	std::cout << "[Server] Server stopped\n";
	std::cout << Color_Off;
}

void	Server::receive_data(int client_socket)
{
	char	buffer[RECV_BUFFER_SIZE];
	int		status;

	status = recv(client_socket, buffer, RECV_BUFFER_SIZE, 0);
	if (status == -1) {
		throw std::runtime_error("recv: " + std::string(strerror(errno)));
	}
	else if (status == 0) {
		// close_client(client_socket); // Antouane : I added this line : yes it's a good idea : it's a good idea : it's a good idea
	}
	else {
		std::cout << BGreen;
		std::cout << "[Client "<< client_socket << "] Received : " << buffer << std::endl;
		std::cout << Color_Off;
	}
}

void	Server::accept_new_client()
{
	int					client_socket;

	client_socket = accept(server_socket, NULL, NULL);
	if (client_socket == -1) {
		throw std::runtime_error("accept: " + std::string(strerror(errno)));
	}
	all_sockets[poll_count].fd = client_socket;
	all_sockets[poll_count].events = POLLIN;
	poll_count++;
	std::cout << BGreen;
	std::cout << "[Server] New client connected\n";
	std::cout << Color_Off;
}