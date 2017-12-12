/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shape_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:46:45 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/12 14:07:34 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Malloc no of shapes into int array.
** Each element: ft_read_shape
*/


unsigned int	*ft_shape_to_array(char *s, int shapes)
{
	unsigned int	*arr;
	int				i;
	char			*tmp;

	arr = (unsigned int*)malloc(sizeof(*arr) * (shapes + 1));
	i = 0;
	while (i < shapes)
	{
		tmp = ft_strndup(s + i + (i * 20), 20);
		arr[i] = ft_read_shape(tmp);
		i++;
	}
	return (arr);

}
