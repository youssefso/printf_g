/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:37:40 by mmostafa          #+#    #+#             */
/*   Updated: 2019/11/19 21:49:20 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

# define IS_INTS (*fmt[0] == 'i' || *fmt[0] == 'd' || *fmt[0] == 'o'|| *fmt[0] == 'u' || *fmt[0] == 'x' || *fmt[0] == 'X')
# define IS_UNS (*conv[0] == 'o'|| *conv[0] == 'u' || *conv[0] == 'x' || *conv[0] == 'X')
# define IS_S (*conv[0] == 'd'|| *conv[0] == 'i')

# define IS_CONVS (*fmt[0] == 'c' || *fmt[0] == 's' || *fmt[0] == 'p')
# define IS_CHAR (*conv[0] == 'c')
# define IS_ADD (*conv[0] == 'p')
# define IS_STR (*conv[0] == 's')
# define IS_FLOAT (*fmt[0] == 'f')
# define CHECK(n)    n < 0 ? i : i + 1
# define IS_PERSENT (*fmt == '%')
# define IS_FLAG (*fmt[0] == '#' || *fmt[0] == '+'|| *fmt[0] == '-' || ft_isdigit(*fmt[0]) || *fmt[0] == 'L' || *fmt[0] == 'l' || *fmt[0] == 'h' || *fmt[0] == '.')
# define POS(X) (X > 0)? X : 0
# define C_POINT	((*flags & POINT) == POINT)
# define C_SUM		((*flags & SUM) == SUM)
# define C_MIN		((*flags & MIN) == MIN)
# define C_ZERO		((*flags & ZERO) == ZERO)
# define C_NUM		((*flags & NUM) == NUM)

# define HH 	0b1
# define H  	0b10
# define LL 	0b100
# define L  	0b1000
# define ML  	0b10000
# define HASH  	0b100000
# define ZERO  	0b1000000
# define MIN  	0b10000000
# define SUM  	0b100000000
# define NUM  	0b1000000000
# define POINT  0b10000000000

typedef struct		s_inf
{
	unsigned long int left;
	unsigned long int right;
	unsigned long int point;
}					t_inf;

#endif
