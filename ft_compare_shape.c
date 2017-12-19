/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare_shape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:39:14 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/19 19:38:16 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* TODO: Use the return value of ft_compare_shape to exit if shape is not found */
/* TODO: Protect mallocs */

/*
** The array 'precoded' holds the 19 possible shapes, which we compare to the
** input using ft_memcmp. If it doesn't match, we shift each of the four lines
** one bit to the right.
*/

void			ft_shift_array(unsigned int *arr, int spaces, int size)
{
	int				i;

	i = 0;
	while (i < size)
	{
		if (spaces < 0)
			arr[i] = arr[i]<<(-spaces);
		else
			arr[i] = arr[i]>>spaces;
		i++;
	}
}

static int			ft_compare_shape(unsigned int *shape, unsigned int n)
{
	int				i;
	int				shifted;
	unsigned int	*shape_copy;
	unsigned int	p;
	unsigned int	precoded[19][4] = 
	{
		{8, 8, 8, 8},
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
		{4, 12, 8, 0}
	};
	unsigned int	*tmp;

	tmp = (unsigned int*)malloc(sizeof(*tmp) * 4);
	shape_copy = shape;
	p = 0;
	while (p < 19)
	{
		i = 0;
		memcpy(tmp, precoded[p], (sizeof(int) * 4));
		shifted = 0;
		while (i < 10)
		{
			if ((ft_memcmp(tmp, shape, sizeof(int) * 4)) == 0)
			{
				ft_memcpy(shape, precoded[p], sizeof(*shape) * 4);
				//printf("shape found!\n");
				return (1);
			}
			// check if rightmost bit is 1 with comparison  &1. If yes, we can't
			// shift to the right.
			// If the last line is empty, shift elements back to original position, 
			//  move array elements down one line and add
			// empty line at the top at tmp[0].
			if (tmp[0] & 1 || tmp[1] & 1 || tmp[2] & 1 || tmp[3] & 1)
			{
				if (tmp[3] == 0)
				{
					ft_shift_array(tmp, (-shifted), 4);
					tmp[3] = tmp[2];
					tmp[2] = tmp[1];
					tmp[1] = tmp[0];
					tmp[0] = 0;
					shifted = 0;
				}
				else
					break;
				i++;
			}
			else
			{
				ft_shift_array(tmp, 1, 4);
				shifted++;
				i++;
			}
		}
		p++;
	}
	printf("shape not found\n");
	return (0);
}

void				ft_compare_shapes(unsigned int **shapes, int n)
{
	int				i;

	i = 0;
	while (i < n)
	{
		ft_compare_shape(shapes[i], n);
		i++;
	}
	shapes[i] = NULL;
}
