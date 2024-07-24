/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:22:20 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/24 11:38:38 by mgallais         ###   ########.fr       */
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
					// accept_new_client();
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