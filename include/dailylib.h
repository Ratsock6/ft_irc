/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dailylib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:59:32 by mgallais          #+#    #+#             */
/*   Updated: 2024/07/11 11:46:03 by mgallais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAILYLIB_H
# define DAILYLIB_H

/*###########################################################################*/
/*                                  Defines                                  */
/*###########################################################################*/
// Custom defines
# define WHITESPACES "\t\n\v\f\r "

/*###########################################################################*/
/*                                 Includes                                  */
/*###########################################################################*/
// Standard includes
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

/*###########################################################################*/
/*                                Structures                                 */
/*###########################################################################*/
// Structure for 2 integers
typedef struct s_2int
{
	int		x;
	int		y;
}	t_2int;

// Structure for 3 integers
typedef struct s_3int
{
	int		x;
	int		y;
	int		z;
}	t_3int;

// Structure for 4 integers
typedef struct s_4int
{
	int		r;
	int		g;
	int		b;
	int		l;
}	t_4int;

// Structure for 2 floats
typedef struct s_2float
{
	float	x;
	float	y;
}	t_2float;

// Structure for 3 floats
typedef struct s_3float
{
	float	x;
	float	y;
	float	z;
}	t_3float;

// Structure for 4 floats
typedef struct s_4float
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_4float;

// Structure for 3 chars
// Can contain a color in RGB format
typedef struct s_RBG
{
	char	r;
	char	g;
	char	b;
}	t_RGB;

// Structure for 4 chars
// Can contain a color in RGBA format
typedef struct s_RBGA
{
	char	r;
	char	g;
	char	b;
	char	a;
}	t_RGBA;

#endif