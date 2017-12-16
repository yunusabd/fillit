/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:09:06 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/16 21:16:06 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* take as input: array of ints, number of shapes
** 
** shift shapes until [other shapes] & [shape] = 0
*/

static int			ft_try_shape(unsigned int *shape, unsigned
		int *map, int line)
{
	int				shifted;
	int				i;
	int				k;
	unsigned int	*tmp;

	shifted = 0;
	i = line;
	k = 0;
	if (line == 4)
		return (1);
	if ((shape[i] & map[k]) == 0)
	{
		map[k] = map[k] | shape[i];
		printf("free space found: %d, map[%d] = %d\n", shape[i], k, map[k]);
		if (ft_try_shape(shape, map + 1, line + 1))
		{
			printf("successfully put line %d\n", line + 1);
			return (1);
		}
	}
	else
	{
		printf("try_shape returned 0\n");
		return (0);
	}
}

static void			ft_remove_shape(unsigned int *shape, unsigned int *map)
{
	int				i;

	i = 0;
	while (i < 4)
	{
		map[i] = map[i] ^ shape[i];
		i++;
	}
}

static int			ft_put_shapes(unsigned int **shapes, unsigned
		int *map, int gridsize, int i)
{
	int				shifted;
	int				k;
	unsigned int	*map_copy;
	//if put_shape returns zero, shift shape until gridsize limit reached
	//then increase k.
	
	shifted = 0;
	k = 0;
	map_copy = map;
	if (!shapes[i])
	{
		printf("Gridsize: %d, i: %d\n", gridsize, i);
		return (1);

	}
	//while (ft_try_shape(shapes[i], map_copy, 0) == 0)
	//{
		if (ft_try_shape(shapes[i], map_copy, 0) == 0)
		{
			
		
		printf("cant place shape %d %d %d %d, ", shapes[i][0], shapes[i][1],
				shapes[i][2], shapes[i][3]);
		if (shifted < gridsize)
		{
			printf("shifted right\n");
			ft_shift_array(shapes[i], 1, 4);
			shifted++;
			ft_put_shapes(shapes, map_copy, gridsize, i);
		}
		else if (k < gridsize)
		{
			printf("shifted down\n");
			ft_shift_array(shapes[i], -shifted, 4);
			shifted = 0;
			k++;
			map_copy += k;
			ft_put_shapes(shapes, map_copy, gridsize, i);
		}
		else if (i == 0)
		{
			printf("increased grid size\n");
			ft_shift_array(shapes[i], -shifted, 4);
			shifted = 0;
			map_copy -= k;
			k = 0;
			gridsize++;
			ft_put_shapes(shapes, map_copy, gridsize, 0);
		}
		else
			return (0);
		}
		else
		{
			ft_put_shapes(shapes, map_copy, gridsize, i + 1);
		}
	//}
	//ft_put_shapes(shapes, map, gridsize, i + 1);
	return (1);
}


static int			ft_print_map(unsigned int *map)
{
	int				i;
	int				k;
	unsigned int	size;
	unsigned int	masked;

	k = 0;
	i = 0;
	size = sizeof(int);
	printf("before while\n");
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

void				ft_set_grid(unsigned int *map, int gridsize)
{
	int				i;
	unsigned int	zero;

	i = 0;
	zero = 0;
	while (i < gridsize)
	{
		map[i] = map[i] & (~zero >> gridsize);
		printf("map[%d]: %d\n", i, map[i] = map[i] & (~zero >> gridsize));
		i++;
	}
}

void				ft_create_map(unsigned int **arr, int shapes)
{
	int				i;
	unsigned int	*map;

	printf("start create map");
	map = (unsigned int*)malloc(sizeof(*arr) * 33);
	printf("sizeof(*map) * 8: %lu\n", sizeof(*map) * 8);
	i= 0;
	while (i < (sizeof(*map) * 8 + 1))
	{
		map[i] = ~0;
		i++;
	}
	ft_set_grid(map, 8);
	ft_put_shapes(arr, map, 8, 0);
	ft_print_map(map);
}
