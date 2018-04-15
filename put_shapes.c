/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:30:42 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 17:08:54 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static uint		*create_map(int *gridsize)
{
	int		i;
	uint	*map;
	uint	zero;

	i = 0;
	if (!(map = (uint*)malloc(sizeof(*map) * 32)))
		return (NULL);
	zero = ~0;
	while (i < *gridsize)
	{
		map[i] = zero >> *gridsize;
		i++;
	}
	while (i < 32)
	{
		map[i] = zero;
		i++;
	}
	return (map);
}

/*
** Shifts a shape back to leftmost position.
*/

int				ft_shift_back(uint *shape)
{
	int		size;
	uint	m;
	uint	*s;

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

static int		put_shapes(uint **s, uint *m, int i, int *gridsize)
{
	int		l;
	int		j;

	l = 0;
	j = 0;
	if (!s[i])
		return (1);
	while (LINE + (ft_shape_height(s[i])) <= (uint)*gridsize)
	{
		while (X < (uint)*gridsize)
		{
			if (!(m[LINE] & (s[i][0] >> X)) && !(m[LINE + 1] & (s[i][1] >> X))
					&& !(m[LINE + 2] & (s[i][2] >> X))
					&& !(m[LINE + 3] & (s[i][3] >> X)))
			{
				ft_toggle_shape(s[i], &m);
				if (put_shapes(s, m, i + 1, gridsize) == 1)
					return (1);
				else
					ft_toggle_shape(s[i], &m);
			}
			X++;
			j++;
		}
		ft_shift_back(s[i]);
		LINE += 1;
		j = 0;
		X = 0;
	}
	if (i == 0)
	{
		LINE = 0;
		X = 0;
		*gridsize += 1;
		free(m);
		m = create_map(gridsize);
		return (put_shapes(s, m, i, gridsize));
	}
	else
	{
		LINE = 0;
		ft_shift_back(s[i]);
		return (0);
	}
}

void			fillit(uint **arr, int *gridsize, int shapes)
{
	int		i;
	uint	*map;
	char	**result;

	map = create_map(gridsize);
	put_shapes(arr, map, 0, gridsize);
	result = print_shapes(arr, gridsize, shapes);
	i = 0;
	while (i < *gridsize)
	{
		ft_putstr(result[i]);
		ft_putchar('\n');
		i++;
	}
}
