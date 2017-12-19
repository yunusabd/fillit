/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:09:06 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/19 14:31:30 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Take as input: array of ints, number of shapes.
** shift shapes until [other shapes] & [shape] = 0
*/

static int			ft_print_map(unsigned int *map)
{
	int				i;
	int				k;
	unsigned int	size;
	unsigned int	masked;

	k = 0;
	i = 0;
	size = sizeof(int);
	while (k < 32)
	{
		i = 0;
		masked = map[k];
		while (i < (size * 8))
		{
			printf("%u ", masked&(1<<31) ? 1 : 0);
			masked = masked<<1;
			i++;
		}
		printf("\n");
		k++;
	}
	return (0);
}

/*
** Sets zeroes for gridsize inside the map. All other bits will be 1.
*/

static void			ft_set_grid(unsigned int *map, int gridsize)
{
	int				i;
	unsigned int	zero;

	i = 0;
	zero = 0;
	while (i < gridsize)
	{
		map[i] = map[i] & (~zero >> gridsize);
		//printf("map[%d]: %d\n", i, map[i] = map[i] & (~zero >> gridsize));
		i++;
	}
}

/*
** Shifts shape back to leftmost position.
*/

static int			ft_shift_back(unsigned int *shape)
{
	int				size;
	unsigned int	m;
	unsigned int	*s;

	s = shape;
	size = sizeof(unsigned int) * 8;
	m = 1<<(size - 1);
	while (!(s[0] & m || s[1] & m || s[2] & m || s[3] & m))
	{
		s[0] = s[0]<<1;
		s[1] = s[1]<<1;
		s[2] = s[2]<<1;
		s[3] = s[3]<<1;
	}
	printf("shifted shape back!\n");
	return (1);
}

/*
** Checks if a shape can be shifted to the right, without exceeding the grid
** size limits. Returns 1 for yes and 0 for no.
*/

static int			ft_can_shift_right(unsigned int *shape, int gridsize)
{
	int				size;
	int				i;
	unsigned int	m;

	size = sizeof(unsigned int) * 8;
	m = 1<<(size - gridsize);
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
** Checks if a shape can be positioned in the map, without actually placing it.
*/

static int			ft_try_shape(unsigned int *shape, unsigned
		int *map, int l)
{
	unsigned int	*m;
	
	m = map;
	if (m[l] & shape[0] || m[l + 1] & shape[1] || m[l + 2] & shape [2] ||
			m[l + 3] & shape[3])
		return (0);
	else
		return (1);
}

/*
** Returns 1 if the first bit on the right is 1.
*/

static int			ft_check_first_bit(unsigned int *shape)
{
	int				i;

	i = 0;
	while (shape[i])
	{
		if ((shape[i] & 1) == 1)
			return (1);
		i++;
	}
	return (0);
}

/*
** Returns the height of the shape
*/

static int			ft_shape_height(unsigned int *s)
{
	if (s[2] == 0)
		return (2);
	if (s[3] == 0)
		return (3);
	else
		return (4);
}


/*
** Puts a shape into the map. Checking has to be done before with ft_try_shape.
*/

static void			ft_set_shape(unsigned int *shape, unsigned
		int *map, int l, int s)
{
	unsigned int	*m;

	m = map;
	if (s == 1)
	{
		m[l] |= shape[0];
		m[l + 1] |= shape[1];
		m[l + 2] |= shape [2];
		m[l + 3] |= shape[3];
	}
	else if (s == 0)
	{
		m[l] ^= shape[0];
		m[l + 1] ^= shape[1];
		m[l + 2] ^= shape [2];
		m[l + 3] ^= shape[3];
	}
}

/*
** Puts the shapes into the map recursively.
*/

static int			ft_put_shapes(unsigned int **shapes, unsigned
		int *map, int i, int gridsize, int line)
{
	if (!shapes[i])
	{
		printf("All shapes put\n");
		return (1);
	}
	// if free space for shape
	if (ft_try_shape(shapes[i], map, line) == 1)
	{
		printf("Free space found for shape [%d]\n", i);
		// put shape into map
		ft_set_shape(shapes[i], map, line, 1);
		// try next shape
		if (ft_put_shapes(shapes, map, i + 1, gridsize, 0) == 0)
		{
			printf("Can't place shape[%d] after trying all places, deleting current shape[%d]\n", i + 1, i);
			ft_set_shape(shapes[i], map, line, 0);

		}
		else
			return (1);
	}
	// if current shape can be shifted to the right, do so
	printf("Can't place shape[%d] %u %u %u %u\n", i, shapes[i][0], shapes[i][1], shapes[i][2], shapes[i][3]);
	if (ft_can_shift_right(shapes[i], gridsize))
	{
		printf("Shape shifted to the right\n");
		ft_shift_array(shapes[i], 1, 4);
		return (ft_put_shapes(shapes, map, i, gridsize, line));
	}
	// if it can't be shifted right, try moving down
	else if ((line + ft_shape_height(shapes[i])) < gridsize)
	{
		printf("Moved to line %d\n", line + 1);
		ft_shift_back(shapes[i]);
		line++;
		return (ft_put_shapes(shapes, map, i, gridsize, line));
	}
	// if can't place first shape or the next, increase
	// grid size
	else if (i == 0)
	{
		printf("Increased gridsize\n");
		gridsize++;
		ft_set_grid(map, gridsize);
		ft_shift_back(shapes[i]);
		return (ft_put_shapes(shapes, map, 0, gridsize, 0));
	}
	else
	{
		ft_shift_back(shapes[i]);
		return (0);
	}

	printf("Can't place shape[%d]\n", i);
}

void				ft_create_map(unsigned int **arr, int shapes)
{
	int				i;
	unsigned int	*map;

	printf("start create map\n");
	map = (unsigned int*)malloc(sizeof(*arr) * 33);
	printf("sizeof(*map) * 8: %lu\n", sizeof(*map) * 8);
	i= 0;
	while (i < (sizeof(*map) * 8 + 1))
	{
		map[i] = ~0;
		i++;
	}
	ft_set_grid(map, 4);
	printf("Set grid finished\n");
	ft_put_shapes(arr, map, 0, 4, 0);
	printf("put shapes finished\n");
	ft_print_map(map);
}
