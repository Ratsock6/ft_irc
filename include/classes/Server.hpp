/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:27:02 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 11:40:50 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "main.hpp"

class Server {
	private :
		/// Attributes :
		static const unsigned short		PORT = 8080;
		static const unsigned short		max_clients = 20;
		static const timeval			select_timeout = {2, 0};

		const int		server_socket;
		int				status;

		// To monitor client sockets:
		struct pollfd	*all_sockets;  // Array of descriptors
		int 			poll_size;  // Size of the descriptor array
		int 			poll_count; // Current number of descriptors in the array		

		/// Private Functions :
		void	create_server_socket();
		void	accept_new_client();
		void	receive_data( int client_socket );
		void	send_data( int client_socket, std::string data );
		void	close_client( int client_socket );

	public :
		/// Constructors & Destructor :
		Server();
		~Server();

		/// Public Functions :
		void	start();
		void	stop();

		/// Exceptions :
		
};
