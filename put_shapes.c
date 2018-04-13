/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:30:42 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/13 18:59:09 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
typedef unsigned int uint;

void	ft_create_map(uint **arr, int *gridsize, int shapes)
{
	uint	*map;
	int		i;
	uint		zero;

	if (!(map = (uint*)malloc(sizeof(*map) * *gridsize)))
		exit(0);
	zero = ~0;
	while (i <= *gridsize)
	{
		map[i] = zero >> *gridsize;
		printf("%u\n", map[i]);
		i++;
	}
}

void	

/*
 * ** Shifts a shape back to leftmost position.
 * */

int             ft_shift_back(uint *shape)
{
	int         size;
	uint        m;
	uint        *s;

	s = shape;
	size = sizeof(unsigned int) * 8;
	m = 1 << (size - 1);
	while (!(s[0] & m || s[1] & m || s[2] & m || s[3] & m))
	{
		s[0] = s[0] << 1;
		s[1] = s[1] << 1;
		s[2] = s[2] << 1;
		s[3] = s[3] << 1;
	}
	return (1);
}
