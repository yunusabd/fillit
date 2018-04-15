/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 19:49:24 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 23:26:36 by vsalai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

unsigned int		read_shape(char *s)
{
	int				i;
	int				j;
	unsigned int	result;

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

static int			min_gridsize(int shapes)
{
	int				i;

	i = 0;
	while (ft_sqrt(shapes + i) == 0)
		i++;
	return (ft_sqrt(shapes + i));
}

static unsigned int	**init_array(int sha)
{
	int				i;
	unsigned int	**arr;

	if (sha > 26 || !(arr = (unsigned int**)malloc(sizeof(*arr) * sha + 1)))
		return (0);
	i = 0;
	while (i < sha)
	{
		if (!(arr[i] = (unsigned int*)malloc(sizeof(**arr) * 5)))
			return (0);
		i++;
	}
	return (arr);
}

int					main(int argc, char **argv)
{
	char			*input;
	unsigned int	**arr;
	int				sha;
	int				*grd;
	// int				i;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit input_file\n");
		return (0);
	}
	if (!(input = read_file(argv[1])))
		return (0);
	if (!(sha = check_input(input)))
		return (0);
	grd = (int*)malloc(sizeof(int));
	*grd = min_gridsize(sha * 4);
	if (!(arr = init_array(sha)))
		return (0);
	input_to_array(input, arr, sha);
	if (!compare_shapes(arr, sha))
		return (0);
	fillit(arr, grd, sha);
	// free(grd);
	// i = 0;
	// while (*arr[i] != '\0')
	// {
	// 	free(arr[i++]);
	// }
	return (0);
}