/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 19:49:24 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/12 22:09:02 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fillit.h"

int		ft_read_shape(char *s)
{
	int		len;
	int		i;
	int		j;
	int		result;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	result = 0;
	while (i < len)
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
//	result = result<<15;
	return (result);
}

int		main(int argc, char **argv)
{
	unsigned int		i;
	int					j;
	unsigned int		size;
	unsigned int		num;
	unsigned int		maxPow = 1<<(31);
	char				*input;
	unsigned int		mask;
	unsigned int		masked;
	unsigned int		*arr;

	printf("Binary: \n%u \n", 1<<31);
	num = 7<<28;
	mask = 0<<31;
	input = ft_read_file(argv[1]);
	printf("Input file formating %s\n", (ft_check_input(input) == 0) ? "invalid" : "valid");
	printf("__________________\n");
	arr = ft_shape_to_array(input, 9);
	ft_compare_shape(arr[3]);
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
	return (0);
}

