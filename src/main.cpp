/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:54:06 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/29 09:55:10 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int	main( int argc, char **argv )
{
	if ( argc != 3 ) {
		std::cerr << BRed;
		std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
		std::cerr << Color_Off;
		return 1;
	}
	
	std::stringstream ss;
	int port;

	ss << argv[1];
	ss >> port;
	if ( ss.fail() ) {
		std::cerr << BRed;
		std::cerr << "Port must be a number\n";
		std::cerr << Color_Off;
		return 1;
	}
	Server server( port , argv[2] );
	
	// server.start();
	// server.stop();

	std::cout << BCyan;
	std::cout << "[Server] /start : start the server\n";
	std::cout << "[Server] /stop : stop the server\n";
	std::cout << "[Server] /exit : exit the program\n";
	std::cout << Color_Off;
	while (server.server_command()) {};

	return 0;
}

