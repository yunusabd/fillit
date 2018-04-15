/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:25:36 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 16:05:30 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**  Helper function to count number of .'s and #'s
*/

static int		ft_count_char(char *s, char c)
{
	int		len;
	int		i;
	int		count;

	len = ft_strlen(s);
	i = 0;
	count = 0;
	while (i < len)
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

/*
** Check if there is a newline at the end of each line.
** After each line, check if there is another newline (more shapes).
** If not, check if end of string, only then return 1.
*/

static int		ft_check_newline(char *s)
{
	int		len;
	int		i;
	int		j;
	int		newlines;

	i = 0;
	newlines = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		j = i;
		while ((s[i] == '.' || s[i] == '#') && i < len)
			i++;
		if (j != i - 4)
			return (0);
		if (s[i] == '\n' && i < len)
		{
			newlines++;
			i++;
			if (newlines != 4 && i == len)
			{
				printf("Newlines check failed\n");
				return (0);
			}
			if (i == len)
			{
				printf("End of file\n");
				return (1);
			}
			else if (s[i] == '\n' && newlines == 4)
			{
				i++;
				// printf("Number of newlines: %d\n", newlines);
				newlines = 0;
			}
			else if (s[i] != '.' && s[i] != '#')
			{
				printf("This baby returns 0\n, s[i]: %c\n", s[i]);
				return (0);
			}
		}
	}
	printf("Last return\n");
	return (0);
}

/*
** Check if char count is a multiple of 20 (for each sqaure) + 1 newline after
** each shape except last.
** Check file content for right number of . and #.
** Return number of shapes.
*/

int				ft_check_input(char *s)
{
	int		len;

	printf("start check_input\n");
	len = strlen(s);
	printf("strlen ran\n");
	if (!(((len + 1) % 21) == 0))
		return (0);
	if (!((ft_count_char(s, '#') % 4) == 0))
		return (0);
	if (!((ft_count_char(s, '.') % 12) == 0))
		return (0);
	if (!(ft_check_newline(s)))
	{
		printf("Check_newlines returned 0\n");
		return (0);
	}
	printf("Check_newlines ran\n");
	printf("%i\n", ((len + 1) / 21));
	return ((len + 1) / 21);
}
