/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:50:38 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/16 20:12:47 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Bitshifts each element of an array by [size] spaces.
*/

void				shift_array(t_uint *arr, int spaces, int size)
{
	int				i;

	i = 0;
	while (i < size)
	{
		if (spaces < 0)
			arr[i] = arr[i] << (-spaces);
		else
			arr[i] = arr[i] >> spaces;
		i++;
	}
}

/*
** The array 'precoded' holds the 19 possible shapes, which we compare to the
** input using ft_memcmp. If it doesn't match, we shift each of the four lines
** one bit to the right using shift_array.
*/

static int			cs(t_uint precoded[19][4], t_uint *shape, int p)
{
	int				i;
	int				shifted;
	t_uint			*tmp;

	tmp = (t_uint*)malloc(sizeof(*tmp) * 4);
	while (p < 19)
	{
		i = 0;
		ft_memcpy(tmp, precoded[p], (sizeof(int) * 4));
		shifted = 0;
		while (i < 10)
		{
			if ((ft_memcmp(tmp, shape, sizeof(int) * 4)) == 0)
			{
				ft_memcpy(shape, precoded[p], sizeof(*shape) * 4);
				shift_back(shape);
				return (1);
			}
			shift_array(tmp, 1, 4);
			shifted++;
			i++;
		}
		p++;
	}
	return (0);
}

/*
** Initializing the array that holds the 19 possible shapes.
*/

static int			init_cs(t_uint *shape)
{
	int					p;
	static t_uint		precoded[19][4] =
	{	{8, 8, 8, 8},
		{15, 0, 0, 0},
		{12, 12, 0, 0},
		{4, 14, 0, 0},
		{14, 4, 0, 0},
		{4, 12, 4, 0},
		{8, 12, 8, 0},
		{14, 2, 0, 0},
		{4, 4, 12, 0},
		{8, 14, 0, 0},
		{12, 8, 8, 0},
		{8, 8, 12, 0},
		{14, 8, 0, 0},
		{12, 4, 4, 0},
		{2, 14, 0, 0},
		{6, 12, 0, 0},
		{8, 12, 4, 0},
		{12, 6, 0, 0},
		{4, 12, 8, 0}	};

	p = 0;
	return (cs(precoded, shape, p));
}

int					compare_shapes(t_uint **shapes, int n)
{
	int				i;

	i = 0;
	while (i < n)
	{
		if (!init_cs(shapes[i]))
			return (0);
		i++;
	}
	shapes[i] = NULL;
	return (1);
}
