/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <yabdulha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:46:45 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/16 20:14:06 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_uint			read_line(char *s)
{
	int				i;
	int				j;
	t_uint			result;

	i = 0;
	j = 0;
	result = 0;
	while (i < 4)
	{
		if (s[i] == '#')
		{
			result = result ^ 1;
			result = result << 1;
		}
		else if (s[i] == '.')
			result = result << 1;
		i++;
		j++;
	}
	result = result >> 1;
	return (result);
}

/*
** For each line of each element run read_line().
** If the shape is not on the upper end of the square, move it up.
*/

void					input_to_array(char *s, t_uint **dst, int shapes)
{
	int				i;
	int				j;

	i = -1;
	while (++i < shapes)
	{
		j = -1;
		while (++j < 4)
		{
			dst[i][j] = read_line(s + i + (j * 5) + (i * 20));
		}
		while (dst[i][0] == 0)
		{
			dst[i][0] = dst[i][1];
			dst[i][1] = dst[i][2];
			dst[i][2] = dst[i][3];
			dst[i][3] = 0;
		}
		dst[i][4] = 0;
		dst[i][5] = 0;
	}
}
