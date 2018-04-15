/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:30:42 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 15:21:52 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

uint			*create_map(int *gridsize)
{
	int		i;
	uint	*map;
	uint	zero;

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

static int	ft_shape_height(uint *s)
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

static void		ft_toggle_shape(uint *shape, uint **map)
{
	uint	*m;
	uint	s_cpy;
	int		x;
	int		l;

	m = *map;
	x = shape[5];
	l = shape[4];
	s_cpy = *shape;
	m[l] ^= (shape[0] >> x);
	m[l + 1] ^= (shape[1] >> x);
	m[l + 2] ^= (shape[2] >> x);
	m[l + 3] ^= (shape[3] >> x);
}

/*
** Shifts a shape back to leftmost position.
*/

int			ft_shift_back(uint *shape)
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

static char		**print_shapes(uint **s, int *gridsize, int shapes)
{
	int		i;
	int		k;
	int		j;
	uint	masked;
	char	**map;

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
			masked = s[i][j] >> s[i][5];
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

static int		print_map(unsigned int *map, int *gridsize)
{
	int		i;
	int		k;
	uint	size;
	uint	masked;

	k = 0;
	i = 0;
	size = sizeof(int);
	while (k < *gridsize + 3)
	{
		i = 0;
		masked = map[k];
		while (i < *gridsize + 3)
		{
			printf("%u ", masked & (1 << (sizeof(uint) * 8 - 1)) ? 1 : 0);
			masked = masked << 1;
			i++;
		}
		printf("\n");
		k++;
	}
	return (0);
}

static int	put_shapes(uint **s, uint *m, int i, int *gridsize)
{
	int		l;
	int		j;
	char	**result;
	int		k;

	l = 0;
	j = 0;
	/*
	result = print_shapes(s, gridsize, i);
	k = 0;
	sleep(1);
	ft_putstr("------------\n");
	#include <stdlib.h>
	system("clear");
	while (k < *gridsize)
	{
		ft_putstr(result[k]);
		ft_putchar('\n');
		k++;
	}
	ft_putstr("------------\n");
	*/
	if (!s[i])
		return (1);
	while (LINE + (ft_shape_height(s[i])) <= *gridsize)
	{
		while (X < *gridsize)
		{
			if (!(m[LINE] & (s[i][0] >> X)) && !(m[LINE + 1] & (s[i][1] >> X)) &&
						!(m[LINE + 2] & (s[i][2] >> X)) && !(m[LINE + 3] & (s[i][3] >> X)))
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

void		fillit(uint **arr, int *gridsize, int shapes)
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
