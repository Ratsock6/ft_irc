/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:27:01 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/24 11:09:56 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void signal_callback_handler(int signum)
{
	std::cout << BRed;
	std::cout << "[Server] Caught signal " << signum << std::endl;
	std::cout << BWhite;
	std::cout << "[Server] Server stopped\n";
	std::cout << Color_Off;
	exit(signum);
}

void Server::signal_handler()
{
	signal(SIGINT, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);
	signal(SIGQUIT, signal_callback_handler);
	signal(SIGKILL, signal_callback_handler);
	signal(SIGSTOP, signal_callback_handler);
	signal(SIGTSTP, signal_callback_handler);
	signal(SIGPIPE, signal_callback_handler);
}