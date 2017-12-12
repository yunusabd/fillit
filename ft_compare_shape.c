/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare_shape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:39:14 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/12 22:12:14 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_compare_shape(int shape)
{
	int		i;
	int		shape_copy;
	unsigned int	tmp;
	unsigned int	p;
	unsigned int	precoded[10] = {8738, 30, 102, 78, 228, 610, 1124, 226, 108};

	shape_copy = shape;
	p = 0;
	while (p < 10)
	{
		i = 0;
		tmp = precoded[p];
		while (i < sizeof(int) * 8)
		{
			if ((shape_copy ^ tmp) == 0)
			{
				printf("shape found: %d\n", precoded[p]);
				return (precoded[p]);
			}
			tmp = tmp<<1;
			i++;
		}
		p++;
	}
	printf("shape not found\n");
	return (0);
}
