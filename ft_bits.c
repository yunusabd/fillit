/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 19:49:24 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/18 22:08:06 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

unsigned int		ft_read_shape(char *s)
{
	int		len;
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
			result = result<<1;
		}
		else if (s[i] == '.')
			result = result<<1;
		i++;
		j++;
	}
	result = result>>1;
	return (result);
}

int		main(int argc, char **argv)
{
	int		i;
	int					j;
	unsigned int		size;
	unsigned int		num;
	unsigned int		maxPow = 1<<(31);
	char				*input;
	unsigned int		mask;
	unsigned int		masked;
	unsigned int		**arr;
	int					shapes;

	printf("Binary: \n%u \n", 1<<31);
	num = 7<<28;
	mask = 0<<31;
	input = ft_read_file(argv[1]);
	shapes = ft_check_input(input);
	printf("Input file formating %s\n", (shapes == 0) ? "invalid" : "valid");
	printf("__________________\n");
	arr = (unsigned int**)malloc(sizeof(*arr) * shapes + 1);
	i = 0;
	while (i < shapes)
	{
		arr[i] = (unsigned int*)malloc(sizeof(**arr) * 4);
		i++;
	}
	ft_input_to_array(input, arr, shapes);
	i = 0;
	while (i < shapes)
	{
		j = 0;
		while (j < 4)
		{
			printf("%d ", arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	ft_compare_shapes(arr, shapes);
	i = 0;
	while (i < shapes)
	{
		j = 0;
		while (j < 4)
		{
			printf("%d ", arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("before create\n");
	ft_create_map(arr, shapes);
	
	/*
	j = 0;
	while (j < 9)
	{
		i = 0;
		size = sizeof(int);
		masked = arr[j];
		printf("decimal: %d\n", arr[j]);
		while (i < (size * 8 - 1))
		{
			printf("%u",masked&maxPow ? 1 : 0);
			masked = masked << 1;
			i++;
		}
		printf("\n");
		printf("______________\n");
		j++;
	}
	*/
	return (0);
}

