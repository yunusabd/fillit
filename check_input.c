/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:25:36 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 18:50:28 by vsalai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**  Helper function to count number of .'s and #'s
*/

static int		count_char(char *s, char c)
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

static int		check_newline(char *s)
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
				return (0);
			if (i == len)
				return (1);
			else if (s[i] == '\n' && newlines == 4)
			{
				i++;
				newlines = 0;
			}
			else if (s[i] != '.' && s[i] != '#')
				return (0);
		}
	}
	return (0);
}

/*
** Check if char count is a multiple of 20 (for each sqaure) + 1 newline after
** each shape except last.
** Check file content for right number of . and #.
** Return number of shapes.
*/

int				check_input(char *s)
{
	int		len;

	len = strlen(s);
	if (!(((len + 1) % 21) == 0))
		return (0);
	if (!((count_char(s, '#') % 4) == 0))
		return (0);
	if (!((count_char(s, '.') % 12) == 0))
		return (0);
	if (!(check_newline(s)))
		return (0);
	return ((len + 1) / 21);
}
