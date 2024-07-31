/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:27:02 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/31 15:18:23 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "main.hpp"

enum server_status_e
{
	STOPPED = 0,
	RUNNING
};

# define POLL_TIMEOUT 500 // 2 seconds

class Server {
	private :
		/// Attributes :
		static const unsigned short		max_clients = 500;
		std::string 					password;
		int								server_status;

		// Server socket :
		unsigned short	port;
		int				server_socket;

		// To monitor client sockets :
		std::vector<struct pollfd>	all_sockets;   // Array of client sockets (0 is the server socket)
		int 						poll_size;     // Size of the descriptor array
		int 						poll_count;    // Current number of descriptors in the array
		std::vector<Client>			clients; 	   // Array of clients
		std::vector<Channel *>		channels;	   // Array of channels

		/// Private Functions :
		// Start
		void	signal_handler();
		void	create_server_socket(); // done
		void	server_loop();
		void	accept_new_client();
		void	receive_data( int client_socket );
		void	send_data( int client_socket, std::string data );
		void	close_client( int client_socket );
		Client&	get_client_by_socket( int client_socket );

		// Stop
		void	close_all_clients();
	
	public :
		/// Constructors & Destructor :
		Server( int port , std::string password );
		~Server();

		/// Public Functions :
		void	start();
		void	stop();
		bool	server_command();
		int new_ID();

		/// Getters & Setters :
		int		get_status() const;
		std::vector<Client> get_clients() const;
		std::vector<Channel *> get_channels() const;
		void add_channel(Channel *channel);
		void add_client(Client client);
		pollfd get_server_socket(void) const;

};