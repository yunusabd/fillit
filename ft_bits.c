/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 19:49:24 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/10 21:01:32 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"

int	read_shape(char *s)
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
	result = result<<15;
	printf("\nResult: \n%d\n", result);
	return (result);
}

int		main()
{
	unsigned int		i;
	unsigned int		size;
	unsigned int		num;
	unsigned int		maxPow = 1<<(31);
	char				*input;
	int					mask;
	int					masked;

	printf("Binary: \n%u \n", 1<<31);
	num = 7<<28;
	mask = 0<<31;
	input = "#...\n#...\n#...\n#...\n";
	masked = read_shape(input);
	i = 0;
	size = sizeof(int);
	printf("Sizeof long long int: %lu\n", sizeof(double));
	printf("Sizeof long int: %lu\n", sizeof(long int));
	printf("Sizeof int: %lu\n", sizeof(int));
	while (i < (size * 8))
	{
		printf("%u ",masked&maxPow ? 1 : 0);
		masked = masked << 1;
		i++;
	}
	return (0);
}

