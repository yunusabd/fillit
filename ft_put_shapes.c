/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:09:06 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/13 18:26:18 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define LINE shapes[i][4]
typedef unsigned int uint;

/*
** Returns the height of the shape. We can assume that the shape is always at
** the upper left position, thanks to ft_shapes_to_array
*/

static int			ft_shape_height(uint *s)
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
** Prints out the map
*/

static char		**ft_print_shapes(uint **s, int *gridsize, int shapes)
{
	int			i;
	int			k;
	int			j;
	uint		masked;
	char		**map;

	map = (char**)malloc(sizeof(*map) * (*gridsize));
	i = 0;
	while (i < *gridsize)
	{
		map[i] = (char*)malloc(sizeof(**map) * (*gridsize + 1));
		j = 0;
		while (j < *gridsize)
		{
			map[i][j] = '.';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	i = 0;
	while (i < shapes)
	{
		j = 0;
		while (j < ft_shape_height(s[i]))
		{
			masked = s[i][j];
			k = 0;
			while (k < *gridsize)
			{
				if (masked & (1 << (sizeof(uint) * 8 - 1)))
					map[s[i][4] + j][k] = 'A' + i;
				masked = masked << 1;
				k++;
			}
			j++;
		}
		i++;
	}
	return (map);
}

static int		ft_print_map(unsigned int *map, int *gridsize)
{
	int			i;
	int			k;
	uint		size;
	uint		masked;

	k = 0;
	i = 0;
	size = sizeof(int);
	while (k < *gridsize)
	{
		i = 0;
		masked = map[k];
		while (i < *gridsize)
		{
			printf("%u ", masked & (1 << (sizeof(uint) * 8 - 1)) ? 1 : 0);
			masked = masked<<1;
			i++;
		}
		printf("\n");
		k++;
	}
	return (0);
}

/*
** Shifts a shape back to leftmost position.
*/

int				ft_shift_back(uint *shape)
{
	int			size;
	uint		m;
	uint		*s;

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

/*
** Checks if a shape can be shifted to the right, without exceeding the grid
** size limits. Returns 1 for yes and 0 for no.
*/

static int		ft_right(uint *shape, int gridsize)
{
	int			size;
	int			i;
	uint		m;

	size = sizeof(unsigned int) * 8;
	m = ~0;
	m = m>>(gridsize - 1);
	i = 0;
	while (i < 4)
	{
		if ((shape[i] & m) != 0)
			return (0);
		i++;
	}
	return (1);
}

/*
** Checks if a row has at least one free spot
*/

static int		ft_line_space(uint line, int gridsize)
{
	uint		mask;

	mask = ~0;
	mask = ~((mask) >> gridsize);
	if (mask == line)
		return (0);
	return (1);
}

/*
** Checks if a shape can be positioned in the map, without actually placing it.
*/

static int		ft_try_shape(uint *shape, uint *map, int l)
{
	uint		*m;

	m = map;
	if (m[l] & shape[0] || m[l + 1] & shape[1] || m[l + 2] & shape[2] ||
			m[l + 3] & shape[3])
		return (0);
	else
		return (1);
}

/*
** Puts or deletes a shape from/into the map.
** Checking has to be done before with ft_try_shape.
** s == 0 is delete mode, which deletes the shape from the map.
** s == 1 is put mode, putting the shape into the map.
*/

static void		ft_toggle_shape(uint *shape, uint *map, int l)
{
	uint		*m;

	m = map;
	m[l] ^= shape[0];
	m[l + 1] ^= shape[1];
	m[l + 2] ^= shape[2];
	m[l + 3] ^= shape[3];
}

/*
** Increases the value pointed to by gridsize, sets the line to 0 and
** shifts shape back.
*/

static int		ft_increase_gridsize(uint *shape, int *gridsize)
{
	printf("increased gridsize\n");
	*gridsize += 1;
	shape[4] = 0;
	ft_shift_back(shape);
	return (1);
}

static int		ft_try_right(uint *map, uint mapline, uint *shape, int gridsize)
{
	if (ft_line_space(mapline, gridsize) && ft_right(shape, gridsize))
	{
		ft_shift_array(shape, 1, 4);
		while (ft_right(shape, gridsize) && (ft_try_shape(shape, map, shape[4]) == 0))
			ft_shift_array(shape, 1, 4);
		return (1);
	}
	return (0);
}

uint			*ft_set_map(int *gridsize)
{
	int			i;
	uint		*map;
	int			zero;

	map = (unsigned int*)malloc(sizeof(*map) * *gridsize);
	i = 0;
	zero = 0;
	while (i < *gridsize)
	{
		map[i] = ((~zero) >> *gridsize);
		i++;
	}
	return (map);
}

void			ft_print(uint **arr, int *gridsize, int shapes)
{
	int			i;
	char		**result;

	result = ft_print_shapes(arr, gridsize, shapes);
	i = 0;
	while (i < *gridsize)
	{
		ft_putstr(result[i]);
		ft_putchar('\n');
		i++;
	}
}

/*
** Puts the shapes into the map recursively.
*/

static int		ft_put_shapes(uint **shapes, uint *map, int i, int *gridsize, int n)
{
	n++;
	if (n > 5)
		return (1);
	printf("executions: %d\n", n);
	ft_print(shapes, gridsize, i);
	printf("------------\n");
	if (!shapes[i])
		return (1);
	if (ft_try_shape(shapes[i], map, LINE) == 1)
	{
		printf("shape fits\n");
		ft_toggle_shape(shapes[i], map, LINE);
		if (ft_put_shapes(shapes, map, i + 1, gridsize, n) == 1)
			return (1);
		else
			ft_toggle_shape(shapes[i], map, LINE);
	}
	if (ft_try_right(map, map[LINE], shapes[i], *gridsize))
	{
		printf("shifting right\n");
		printf("------------\n");
		return (ft_put_shapes(shapes, map, i, gridsize, n));
	}
	else if (ft_line_space(map[LINE], *gridsize)
			&& (LINE + ft_shape_height(shapes[i])) < *gridsize)
	{
		printf("shifting down\n");
		printf("------------\n");
		ft_shift_back(shapes[i]);
		LINE += 1;
		return (ft_put_shapes(shapes, map, i, gridsize, n));
	}
	else if (i == 0 && ft_increase_gridsize(shapes[i], gridsize))
	{
		printf("increased gridsize\n");
		printf("------------\n");
		free(map);
		map = ft_set_map(gridsize);
		return (ft_put_shapes(shapes, map, 0, gridsize, n));
	}
	LINE = 0;
	ft_shift_back(shapes[i]);
	printf("Return 0\n");
	return (0);
}

void			ft_create_map(uint **arr, int *gridsize, int shapes)
{
	int			i;
	uint		*map;
	char		**result;

	map = ft_set_map(gridsize);
	ft_put_shapes(arr, map, 0, gridsize, 0);
	ft_print_map(map, gridsize);
	result = ft_print_shapes(arr, gridsize, shapes);
	i = 0;
	while (i < *gridsize)
	{
		ft_putstr(result[i]);
		ft_putchar('\n');
		i++;
	}
}
