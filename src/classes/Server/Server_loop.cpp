/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:22:20 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/24 14:31:44 by aallou-v         ###   ########.fr       */
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
		status = poll(all_sockets.data(), poll_count, timeout.tv_sec * 1000);
		if (status == -1) {
			throw std::runtime_error( strerror(errno) );
		}
		else if (status == 0) {
			std::cout << BGray << "[Server] Waiting...\n" << Color_Off;
			continue;
		}

		// Check for events
		for (i = 0; i < poll_count; i++)
		{
			if (all_sockets[i].revents & POLLIN)
			{
				if (all_sockets[i].fd == server_socket)
				{
					accept_new_client();
				}
				else
				{
					// receive_data(all_sockets[i].fd);
				}
			}
		}
	}
	std::cout << BWhite;
	std::cout << "[Server] Server stopped\n";
	std::cout << Color_Off;
}

void Server::accept_new_client()
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