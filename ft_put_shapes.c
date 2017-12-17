/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:09:06 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/17 22:01:43 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Take as input: array of ints, number of shapes.
** shift shapes until [other shapes] & [shape] = 0
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
		printf("map[%d]: %d\n", i, map[i] = map[i] & (~zero >> gridsize));
		i++;
	}
}

static int			ft_try_shape(unsigned int *shape, unsigned
		int *map, int line)
{
	int				i;
	int				k;

	i = line;
	k = 0;
	if (line == 32)
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
		else
		{
			printf("next line doesnt fit, abort\n");
			map[k] = map[k] ^ shape[i];
			return (0);
		}
	}
	else
	{
		return (0);
	}
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


static int			ft_shift_right(unsigned int *shape)
{
	int				i;

	i = 0;
	if (ft_check_first_bit(shape) == 0)
	{
		while (shape[i])
		{
			shape[i] = shape[i]>>1;
			i++;
		}
		return (1);
	}
	return (0);
}

/* Trys to shift down the array by one line, if last line is empty.
** Returns 1 on success.
*/

static int			ft_move_down_array(unsigned int *arr, int n)
{
	if (!arr[n])
	{
		while (n)
		{
			arr[n] = arr[n - 1];
			n--;
		}
		return (1);
	}
	return (0);
}

static void			ft_remove_shape(unsigned int *shape, unsigned int *map)
{
	int				i;

	i = 0;
	while (i < 32)
	{
		map[i] = map[i] ^ shape[i];
		i++;
	}
}

static int			ft_put_shapes(unsigned int **shapes, unsigned
		int *map, int i, unsigned int **sorted)
{
	int				gridsize;

	gridsize = 8;
	//if put_shape returns zero, shift shape until gridsize limit reached
	//then increase k.
	if (!shapes[i])
	{
		printf("Gridsize: %d, i: %d\n", gridsize, i);
		return (1);

	}
	if (!sorted[i])
	{
		sorted[i] = (unsigned int*)malloc(sizeof(*sorted));
		sorted[i] = ft_memcpy(sorted[i], shapes[i], 32);
	}
	if (ft_try_shape(sorted[i], map, 0) == 1)
		return (ft_put_shapes(shapes, map, i + 1, sorted));
	else
	{
		printf("Entered else\n");
		if (ft_put_shapes(shapes, map, i + 1, sorted) == 0)
		{
			ft_remove_shape(sorted[i], map);
			if (ft_shift_right(sorted[i]))
				ft_put_shapes(shapes, map, i, sorted);
			else if (ft_move_down_array(sorted[i], 32) == 1)
				ft_put_shapes(shapes, map, i, sorted);
			else if (i == 0)
			{
				sorted[i] = 0;
				ft_set_grid(map, gridsize++);
				ft_put_shapes(shapes, map, i, sorted);
			}
			else
				return (0);
		}
	}
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

void				ft_create_map(unsigned int **arr, int shapes, unsigned int
		**sorted)
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
	ft_set_grid(map, 4);
	ft_put_shapes(arr, map, 0, sorted);
	ft_print_map(map);
}
