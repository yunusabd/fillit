/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:51:22 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/16 20:13:17 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			print_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

/*
** Returns the height of a shape.
*/

int				shape_height(t_uint *s)
{
	if (s[1] == 0)
		return (1);
	if (s[2] == 0)
		return (2);
	if (s[3] == 0)
		return (3);
	else
		return (4);
}

/*
** Puts or removes a shape from the map.
*/

void			toggle_shape(t_uint *s, t_uint **map)
{
	t_uint	*m;
	t_uint	s_cpy;
	int		x;
	int		y;

	m = *map;
	x = s[4];
	y = s[5];
	s_cpy = *s;
	m[y] ^= (s[0] >> x);
	m[y + 1] ^= (s[1] >> x);
	m[y + 2] ^= (s[2] >> x);
	m[y + 3] ^= (s[3] >> x);
}
