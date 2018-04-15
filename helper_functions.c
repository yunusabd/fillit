/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:51:22 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 18:16:23 by vsalai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				ft_shape_height(uint *s)
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

void			ft_toggle_shape(uint *shape, uint **map)
{
	uint    *m;
	uint    s_cpy;
	int     x;
	int     l;

	m = *map;
	x = shape[5];
	l = shape[4];
	s_cpy = *shape;
	m[l] ^= (shape[0] >> x);
	m[l + 1] ^= (shape[1] >> x);
	m[l + 2] ^= (shape[2] >> x);
	m[l + 3] ^= (shape[3] >> x);
}
