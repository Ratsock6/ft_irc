/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:54:06 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/11 11:06:57 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int	main( int argc, char **argv )
{
	if ( argc != 3 )
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
		return 1;
	}

	(void)argv;

	return 0;
}
