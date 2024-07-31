/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:54:06 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/31 10:27:19 by mgallais         ###   ########.fr       */
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
	while (server.server_command()) {}; // loop until exit command


	/**************test val *****************************/
	// try{
	// 	Server server(4242, "1234");
	// 	Client client("michel", 1, server.new_ID(), true);
	// 	Client client2("jean", 2, server.new_ID(), true);
	// 	Channel channel("test", client);
	// 	channel.add_user_by_admin(client2, client);
	// 	channel.set_password("1234", client);
	// 	std::cout << channel.get_password() << std::endl;
	// 	server.add_channel(&channel);
	// 	std::vector<Channel *> channels = server.get_channels();
	// 	Channel channell = *channels[0];
	// 	client.setAdmin(true);
	// 	std::cout << "channel name " << channell.get_channel_name() << " channel pwd " << channell.get_password() << std::endl;
	// 	parsing_command(argv[2], server.get_channels(), client);
	// }
	// catch (std::exception &e){
	// 	std::cerr << BRed;
	// 	std::cerr << e.what() << std::endl;
	// 	std::cerr << Color_Off;
	// }
	/******************************************************/
	// server.start();
	// server.stop();

	return 0;
}

