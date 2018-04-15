/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 19:49:24 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 18:46:16 by vsalai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

unsigned int		read_shape(char *s)
{
	int		i;
	int		j;
	unsigned int		result;

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
			result = result<<1;
		i++;
		j++;
	}
	result = result >> 1;
	return (result);
}

static int			min_gridsize(int shapes)
{
	int				i;

	i = 0;
	while (ft_sqrt(shapes + i) == 0)
		i++;
	return (ft_sqrt(shapes + i));
}

int		main(int argc, char **argv)
{
	int		i;
	char				*input;
	unsigned int		mask;
	unsigned int		**arr;
	int					shapes;
	int					*gridsize;

	argc += 0;
	// error checking for number of 
	mask = 0<<31;
	input = read_file(argv[1]);
	// error checking for invalid shape
	shapes = check_input(input);

	// maybe we don't need it
	gridsize = (int*)malloc(sizeof(int));
	*gridsize = min_gridsize(shapes * 4);
	arr = (unsigned int**)malloc(sizeof(*arr) * shapes + 1);
	i = 0;
	while (i < shapes)
	{
		arr[i] = (unsigned int*)malloc(sizeof(**arr) * 5);
		i++;
	}
	input_to_array(input, arr, shapes);
	compare_shapes(arr, shapes);
	fillit(arr, gridsize, shapes);
	free(gridsize);
	// more freeing needs to be done
	// every time there is a malloc things need to get freed
	return (0);
}
