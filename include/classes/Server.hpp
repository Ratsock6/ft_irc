/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:27:02 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 09:35:25 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "main.hpp"

class Server {
	private :
		static unsigned short	PORT = 4242;
		static timeval			select_timeout = {2, 0};

		int						server_socket;
		
	public :
		Server();
		~Server();
		Server( const Server &src );
		Server &operator=( const Server &src );

		void	start();
		void	stop();
};