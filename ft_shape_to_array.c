/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shape_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:46:45 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 17:07:11 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Malloc no of shapes into int array.
** Each element: ft_read_shape
*/

void				ft_input_to_array(char *s, unsigned int **dst, int shapes)
{
	int				i;
	int				j;
	char			*tmp;

	i = 0;
	while (i < shapes)
	{
		//dst[i] = (unsigned int*)malloc(sizeof(dst) * 4);
		j = 0;
		tmp = (char*)malloc(sizeof(*tmp) * 4);
		while (j < 4)
		{
			tmp = ft_strndup(s + i + (j * 5) + (i * 20), 4);
			dst[i][j] = ft_read_shape(tmp);
			j++;
		}
		dst[i][4] = 0;
		dst[i][5] = 0;
		free(tmp);
		i++;
	}
}
