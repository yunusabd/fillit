/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:30:42 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/14 16:37:04 by yabdulha         ###   ########.fr       */
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

/*
 ** Checks if a shape can be positioned in the map, without actually placing it.
 */

static int		ft_try_shape(uint *shape, uint *map, int l)
{
	uint	*m;

	m = map;
	if (m[l] & shape[0] || m[l + 1] & shape[1] || m[l + 2] & shape[2] ||
			m[l + 3] & shape[3])
		return (0);
	else
		return (1);
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

static void     ft_toggle_shape(uint *shape, uint **map, int l)
{
	uint        *m;

	m = *map;
	m[l] ^= shape[0];
	m[l + 1] ^= shape[1];
	m[l + 2] ^= shape[2];
	m[l + 3] ^= shape[3];
}

/*
 ** Shifts a shape back to leftmost position.
 */

int             ft_shift_back(uint *shape)
{
	int         size;
	uint        m;
	uint        *s;

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

static char     **print_shapes(uint **s, int *gridsize, int shapes)
{
	int         i;
	int         k;
	int         j;
	uint        masked;
	char        **map;

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

static int      print_map(unsigned int *map, int *gridsize)
{
	int         i;
	int         k;
	uint        size;
	uint        masked;

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
			masked = masked<<1;
			i++;
		}
		printf("\n");
		k++;
	}
	return (0);
}

static int	put_shapes(uint **s, uint *m, int i, int *gridsize)
{
	int	l;
	int	j;
	int	k;
	char	**result;

	l = 0;
	j = 0;
	result = print_shapes(s, gridsize, i);
	k = 0;
	ft_putstr("------------------\n");
	while (k < *gridsize)
	{
		ft_putstr(result[k]);
		ft_putchar('\n');
		k++;
	}
	//print_map(m, gridsize);
	ft_putstr("------------------\n");
	if (!s[i])
	{
		printf("finished\n");
		return (1);
	}
	while (j < *gridsize && (m[LINE] & s[i][0] || m[LINE + 1] & s[i][1] ||
				m[LINE + 2] & s[i][2] || m[LINE + 3] & s[i][3]))
	{
		ft_shift_array(s[i], 1, 4);
		printf("shifting\n");
		j++;
	}
	if (!(m[LINE] & s[i][0] || m[LINE + 1] & s[i][1] || m[LINE + 2] & s[i][2] ||
			m[LINE + 3] & s[i][3]))
	{
		printf("toggle shape\n");
		ft_toggle_shape(s[i], &m, LINE);
		if (put_shapes(s, m, i + 1, gridsize) == 1)
			return (1);
		else
			ft_toggle_shape(s[i], &m, LINE);
	}
	if (LINE + (ft_shape_height(s[i])) < *gridsize)
	{
		printf("line down\n");
		ft_shift_back(s[i]);
		LINE += 1;
		return (put_shapes(s, m, i, gridsize));
	}
	else if (i == 0)
	{
		printf("increasing gridsize\n");
		LINE = 0;
		ft_shift_back(s[i]);
		*gridsize += 1;
		free(m);
		m = create_map(gridsize);
		return (put_shapes(s, m, i, gridsize));
	}
	else
	{
		printf("form %i doesnt fit\n", i);
		//ft_toggle_shape(s[i], &m, LINE);
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
	print_map(map, gridsize);
	put_shapes(arr, map, 0, gridsize);
	print_map(map, gridsize);
	result = print_shapes(arr, gridsize, shapes);
	i = 0;
	while (i < *gridsize)
	{
		ft_putstr(result[i]);
		ft_putchar('\n');
		i++;
	}
}












