/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:54:06 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/29 15:24:46 by vsoltys          ###   ########.fr       */
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
	std::cout << "hacking NASA 0%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 10%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 20%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 30%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 40%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 50%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 60%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 70%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 80%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 90%..." << std::endl;
	sleep(1);
	std::cout << "hacking NASA 100%..." << std::endl;

	std::cout << BCyan;
	std::cout << "[Server] /start : start the server if not running\n";
	std::cout << "[Server] /stop : stop the server if running\n";
	std::cout << "[Server] /exit : exit the program if not running\n";
	std::cout << "[Server] /help : display this help\n";
	std::cout << Color_Off;
	while (server.server_command()) {}; // loop until exit command


	/**************test val *****************************/
	// Client client("michel", 1, server.new_ID(), true);
	// Channel channel("test", client);
	// try{
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

