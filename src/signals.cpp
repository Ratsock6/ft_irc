/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:27:01 by mgallais          #+#    #+#             */
/*   Updated: 2024/08/13 10:53:12 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

// Don't leak 
void signal_callback_handler(int signum)
{
	Server *server = Server::get_instance(); // Get the instance of the server
	std::cout << BRed;
	std::cout << "\r[Server] Caught signal " << signum << std::endl;
	std::cout << Color_Off;
	server->stop();
	Server::destroy_instance();
	exit(signum);
}

void Server::signal_handler()
{
	signal(SIGINT, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);
	signal(SIGQUIT, signal_callback_handler);
	signal(SIGTSTP, signal_callback_handler);
}