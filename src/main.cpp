/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoltys <vsoltys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:54:06 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/23 12:54:51 by vsoltys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int	main( int argc, char **argv )
{
	if ( argc != 3 ) {
		std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
		return 1;
	}
	int	port = atoi( argv[1] );
	try{
		std::string str(argv[2]);
		parsing_command(str);
	}
	catch (std::exception &e){
		std::cerr << e.what() << std::endl;
		return 1;
	}
	if ( !port ) {
		std::cerr << "Port must be a number\n";
		return 1;
	}
	
	return 0;
}

