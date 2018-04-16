/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 19:49:24 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/16 22:00:02 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Calculate the minimum gridsize depending on the number of shapes.
*/

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
	arr[i] = NULL;
	return (arr);
}

int					main(int argc, char **argv)
{
	char			*input;
	unsigned int	**arr;
	int				sha;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit input_file\n");
		return (0);
	}
	input = read_file(argv[1]);
	if (!input)
		print_error();
	if (!(sha = check_input(input)))
		print_error();
	if (!(arr = init_array(sha)))
		print_error();
	input_to_array(input, arr, sha);
	if (!compare_shapes(arr, sha))
		print_error();
	fillit(arr, min_gridsize(sha * 4), sha);
	return (0);
}
