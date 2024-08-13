/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:22:20 by mgallais          #+#    #+#             */
/*   Updated: 2024/08/13 11:17:08 by mgallais         ###   ########.fr       */
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
		if (DEBUG)
			std::cout << "poll count: " << poll_count << std::endl;
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
	int					status;

	message.str() = client.getMessageBuffer().str();
	status = recv(client_socket, buffer, RECV_BUFFER_SIZE, MSG_DONTWAIT);
	if (status == -1) {
		throw std::runtime_error("recv: " + std::string(strerror(errno)));
	}
	else if (status == 0) { // Client disconnected
		close_client(client_socket);
	}
	else {
		message << std::string(buffer, status);
		client.setMessageBuffer(message);
		
		std::cout << BGreen;
		std::cout << "[Server] Received message from client " << client_socket << ": " << std::endl << message.str();
		std::cout << Color_Off;
		
		if (message.str().size() >= 2 && message.str().substr(message.str().size() - 2) == MESSAGE_END) {
			
			try{
				pre_parsing(message.str(), channels, get_client_by_socket(client_socket), *this);
				if (this->new_client == true)
				{
					send_RPL_message(1, this, get_client_by_socket(client_socket), NULL, "");
					send_RPL_message(2, this, get_client_by_socket(client_socket), NULL, "");
					send_RPL_message(3, this, get_client_by_socket(client_socket), NULL, "");
					send_RPL_message(4, this, get_client_by_socket(client_socket), NULL, "");
					send_RPL_message(5, this, get_client_by_socket(client_socket), NULL, "");
					this->new_client = false;
				}
			}
			catch (std::exception &e){
				std::cerr << BRed;
				std::cerr << "[Server] Error : " << e.what() << std::endl;
				std::cerr << Color_Off;
			}
			
			message.str("");
			message.clear();
		}
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

	// Set the client socket to non-blocking mode
	if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
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
	new_socket.revents = 0;
	all_sockets[poll_count]	= new_socket;
	poll_count++;

	Client new_client("temp_name", all_sockets[poll_count - 1].fd, new_ID(), false);
	new_client.setNickname("temp_nick");
	//new_client.setRealname("temp_realname");
	this->clients.push_back(new_client);
	/**************test val *****************************/

	// Client test_client("test_client", 2, new_ID(), true);
	// Channel test("test", new_client);
	// test.send_private_msg("YOUHOUU", test_client, new_client);
	/******************************************************/
	
	std::cout << BGreen;
	std::cout << "[Server] New client connected : " << client_socket << "\n";
	std::cout << Color_Off;
	this->new_client = true;
}