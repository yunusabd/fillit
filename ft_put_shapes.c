/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:09:06 by yabdulha          #+#    #+#             */
/*   Updated: 2018/01/08 20:36:10 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Returns the height of the shape, to see if shape height plus line is less
** than the gridsize limit.
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
** Prints out the map
*/

static char			**ft_print_shapes(unsigned int **s, int *gridsize, int shapes)
{
	int				i;
	int				k;
	int				j;
	unsigned int	size;
	unsigned int	masked;
	char			**map;


	// make map and fill with dots
	map = (char**)malloc(sizeof(*map) * *gridsize);
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
		map[i][j] = '\n';
		i++;
	}
	// for each form, go to corresponding line
	i = 0;
	while (i < shapes)
	{
		j = 0;
		while (j < ft_shape_height(s[i]))
		{
			// go to the line saved in the shape
			masked = s[i][j];
			k = 0;
			while (k < *gridsize)
			{
				if (masked&(1<<31))
					map[s[i][4] + j][k] = 'A' + i;
				masked = masked<<1;
				k++;
			}
			j++;
		}
		i++;
	}
	printf("finished filling map\n");
	return (map);
}

static int			ft_print_map(unsigned int *map, int *gridsize)
{
	int				i;
	int				k;
	unsigned int	size;
	unsigned int	masked;

	k = 0;
	i = 0;
	size = sizeof(int);
	while (k < *gridsize)
	{
		i = 0;
		masked = map[k];
		while (i < *gridsize)
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

static void			ft_set_grid(unsigned int *map, int *gridsize)
{
	int				i;
	unsigned int	zero;

	i = 0;
	zero = 0;
	while (i < *gridsize)
	{
		map[i] = map[i] & (~zero >> *gridsize);
		i++;
	}
}

/*
** Shifts a shape back to leftmost position.
*/

int			ft_shift_back(unsigned int *shape)
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
	// printf("shifted shape back!\n");
	return (1);
}

/*
** Checks if a shape can be shifted to the right, without exceeding the grid
** size limits. Returns 1 for yes and 0 for no.
*/

static int			ft_can_shift_right(unsigned int *shape, int *gridsize)
{
	int				size;
	int				i;
	unsigned int	m;

	size = sizeof(unsigned int) * 8;
	m = ~0;
	m = m>>(*gridsize - 1);
	//m = 1<<(size - *gridsize);
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
** Puts or deletes a shape from/into the map.
** Checking has to be done before with ft_try_shape.
** s == 0 is delete mode, which deletes the shape from the map.
** s == 1 is put mode, putting the shape into the map.
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
		int *map, int i, int *gridsize)
{
	if (!shapes[i])
	{
		printf("All shapes put, gridsize %d\n", *gridsize);
		return (1);
	}
	if (ft_try_shape(shapes[i], map, shapes[i][4]) == 1)
	{
		ft_set_shape(shapes[i], map, shapes[i][4], 1);
		if (ft_put_shapes(shapes, map, i + 1, gridsize) == 1)
			return (1);
		else
			ft_set_shape(shapes[i], map, shapes[i][4], 0);
	}
	if (ft_can_shift_right(shapes[i], gridsize))
	{
		ft_shift_array(shapes[i], 1, 4);
		while ((ft_can_shift_right(shapes[i], gridsize) == 1) &&
				ft_try_shape(shapes[i], map, shapes[i][4]) == 0)
			ft_shift_array(shapes[i], 1, 4);
		return (ft_put_shapes(shapes, map, i, gridsize));
	}
	else if ((shapes[i][4] + ft_shape_height(shapes[i])) < *gridsize)
	{
		ft_shift_back(shapes[i]);
		shapes[i][4] += 1;
		return (ft_put_shapes(shapes, map, i, gridsize));
	}
	else if (i == 0)
	{
		printf("increased gridsize\n");
		*gridsize += 1;
		shapes[i][4] = 0;
		ft_set_grid(map, gridsize);
		ft_shift_back(shapes[i]);
		return (ft_put_shapes(shapes, map, 0, gridsize));
	}
	else
	{
		shapes[i][4] = 0;
		ft_shift_back(shapes[i]);
		return (0);
	}
}

void				ft_create_map(unsigned int **arr, int *gridsize, int shapes)
{
	int				i;
	unsigned int	*map;
	char			**result;

	map = (unsigned int*)malloc(sizeof(*arr) * 33);
	i= 0;
	while (i < (sizeof(*map) * 8 + 1))
	{
		map[i] = ~0;
		i++;
	}
	ft_set_grid(map, gridsize);
	ft_put_shapes(arr, map, 0, gridsize);
	ft_print_map(map, gridsize);
	result = ft_print_shapes(arr, gridsize, shapes);
	i = 0;
	while (i < *gridsize)
	{
		ft_putstr(result[i]);
		i++;
	}
}
