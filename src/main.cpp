/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:54:06 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 17:47:09 by vsoltys          ###   ########.fr       */
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
	
	Server server( port );

	/*****************test parsing command a retirer ****/
	Client client("michel", 1, 1, true);
	Client client2("jean", 2, 2, false);
	Channel channel("channel", client);
	std::vector<Channel> channels;
	channel.add_user_by_admin(client2, client);
	std::vector<Client> clients = channel.get_users_list();
	channels.push_back(channel);
	try{
		parsing_command( argv[2], channels, client);
		parsing_command( "/mode #channel +i", channels, client2);
	}
	catch(const std::exception& e){
		std::cerr << BRed;
		std::cerr << e.what() << std::endl;
		std::cerr << Color_Off;
	}
	/****************************************************/
	//server.start();


	return 0;
}

