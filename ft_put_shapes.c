/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:09:06 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/15 18:34:19 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* take as input: array of ints, number of shapes
** 
** shift shapes until [other shapes] & [shape] = 0
*/

static int			ft_try_line(unsigned int *shape, unsigned
		int *map, int gridsize, int line)
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
	printf("line = %d %d %d %d\n", shape[0], shape[1], shape[2], shape[3]);
	if ((shape[i] & map[k]) == 0)
	{
		map[k] = map[k] | shape[i];
		printf("free space found: %d, map[%d] = %d\n", shape[i], k, map[k]);
		if (ft_try_line(shape, map + 1, gridsize, line + 1))
		{
			printf("successfully put line %d\n", line + 1);
			return (1);
		}
	}
	else
		return (0);
}

static int			ft_try_shapes(unsigned int **shapes, unsigned
		int *map, int gridsize, int k, int shifted)



static int			ft_put_shape(unsigned int **arr, unsigned int *map, int element, int gridsize)
{
	int				i;
	int				k;
	unsigned int	size;
	unsigned int	masked;

	j = 0;
	k = 0;
	i = 0;
	if (element >= 3)
		return (1);
	ft_try_shape(arr[element], map, gridsize, 3);
	printf("put first shape\n");
	ft_try_shape(arr[element + 1], map, gridsize, 3);
	k = 0;
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
		map[i] = 0;
		i++;
	}
	ft_try_shapes(arr, map, 5, 3);
}
