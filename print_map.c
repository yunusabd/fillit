/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:40:39 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 15:47:21 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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


char			**print_shapes(uint **s, int *gridsize, int shapes)
{
	int		i;
	int		k;
	int		j;
	uint	masked;
	char	**map;

	map = init_map(gridsize);	
	i = 0;
	while (i < shapes)
	{
		j = 0;
		while (j < ft_shape_height(s[i]))
		{
			masked = s[i][j] >> X;
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
