/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:27:02 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 15:42:19 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "main.hpp"

enum server_status
{
	STOPPED = 0,
	RUNNING
};

class Server {
	private :
		/// Attributes :
		static const unsigned short		max_clients = 500;
		const timeval					timeout; // 2 seconds

		// Server socket :
		unsigned short	port;
		int				server_socket;
		int				server_status;

		// To monitor client sockets :
		struct pollfd		*all_sockets;  // Array of descriptors
		int 				poll_size;     // Size of the descriptor array
		int 				poll_count;    // Current number of descriptors in the array
		// std::vector<Client>	clients; 	   // Array of clients
		// std::vector<Channel>	channels;	   // Array of channels

		/// Private Functions :
		// Start
		void	create_server_socket(); // done
		void	server_loop();
		void	accept_new_client();
		void	receive_data( int client_socket );
		void	send_data( int client_socket, std::string data );
		void	close_client( int client_socket );

		// Stop
		void	close_all_clients();
		void	close_server_socket();

	public :
		/// Constructors & Destructor :
		Server( int port );
		~Server();

		/// Public Functions :
		void	start();
		void	stop();

		/// Exceptions :
		
};
