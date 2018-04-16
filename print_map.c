/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:40:39 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/16 20:10:35 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Creates a char array with the final gridsize and fills it with dots.
*/

static char		**init_map(int *gridsize)
{
	char	**map;
	int		i;
	int		j;

	map = (char**)malloc(sizeof(*map) * (*gridsize));
	i = 0;
	j = 0;
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
	return (map);
}


/*
** Converts the shapes into letters of the alphabet, putting them on the map
** using the X and Y values stored within each shape.
*/

char			**print_shapes(t_uint **s, int *gridsize, int shapes)
{
	int		i;
	int		k;
	int		j;
	t_uint	masked;
	char	**map;

	map = init_map(gridsize);
	i = 0;
	while (i < shapes && (j = 0) == 0)
	{
		while (j < shape_height(s[i]) && (k = 0) == 0)
		{
			masked = s[i][j] >> X;
			while (k < *gridsize)
			{
				if (masked & (1 << (sizeof(t_uint) * 8 - 1)))
					map[Y + j][k] = 'A' + i;
				masked = masked << 1;
				k++;
			}
			j++;
		}
		i++;
	}
	return (map);
}
