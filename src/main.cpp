/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:54:06 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 13:01:03 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int	main( int argc, char **argv )
{
	if ( argc != 3 ) {
		std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
		return 1;
	}
	
	std::stringstream ss;
	int port;

	ss << argv[1];
	ss >> port;
	if ( ss.fail() ) {
		std::cerr << "Port must be a number\n";
		return 1;
	}

	Server server( port );

	server.start();


	return 0;
}
