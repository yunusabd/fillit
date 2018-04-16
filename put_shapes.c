/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <yabdulha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:30:42 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/16 20:09:46 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Creates a map, setting all spaces to 1, except the area specified by
** gridsize.
*/

static t_uint	*create_map(int *gridsize)
{
	int		i;
	t_uint	*map;
	t_uint	zero;

	i = 0;
	if (!(map = (t_uint*)malloc(sizeof(*map) * 32)))
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

int				shift_back(t_uint *shape)
{
	int		size;
	t_uint	m;
	t_uint	*s;

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

static int		put_shapes(t_uint **s, t_uint *m, int i, int *gridsize)
{
	if (!s[i])
		return (1);
	while (Y + (shape_height(s[i])) <= (t_uint)*gridsize)
	{
		while (X < (t_uint)*gridsize)
		{
			if (!(m[Y] & (s[i][0] >> X)) && !(m[Y + 1] & (s[i][1] >> X))
					&& !(m[Y + 2] & (s[i][2] >> X))
					&& !(m[Y + 3] & (s[i][3] >> X)))
			{
				toggle_shape(s[i], &m);
				if (put_shapes(s, m, i + 1, gridsize) == 1)
					return (1);
				else
					toggle_shape(s[i], &m);
			}
			X++;
		}
		Y += 1;
		X = 0;
	}
	return (increase_gridsize(s, m, i, gridsize));
}

/*
** Checks if the gridsize can be increased, otherwise returns zero.
*/

int				increase_gridsize(t_uint **s, t_uint *m, int i, int *gridsize)
{
	if (i == 0)
	{
		Y = 0;
		X = 0;
		*gridsize += 1;
		free(m);
		m = create_map(gridsize);
		return (put_shapes(s, m, i, gridsize));
	}
	else
	{
		Y = 0;
		return (0);
	}
}

void			fillit(t_uint **arr, int *gridsize, int shapes)
{
	int		i;
	t_uint	*map;
	char	**result;

	if (!(map = create_map(gridsize)))
		print_error();
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
