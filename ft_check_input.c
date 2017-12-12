/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:25:36 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/12 12:06:41 by yabdulha         ###   ########.fr       */
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
** After each line, check if there is another newline.
** If not, check if end of string, only then return 1.
*/

static int		ft_check_newline(char *s)
{
	int		len;
	int		i;
	int		j;
	int		newlines;

	i = 0;
	while (i < len)
	{
		j = i;
		while ((s[i] == '.' || s[i] == '#') && i < len)
			i++;
		if (j != i - 4)
			return (0);
		if (s[i] == '\n' && i < len)
		{
			i++;
			if (i == len)
				return (1);
			else if (s[i] == '\n')
				i++;
			else if (s[i] != '.' && s[i] != '#')
				return (0);
		}
	}
	return (0);
}

/*
** TODO Check if there are 4 * # and 12 * . in each shape
*/

/*
** Alternative TODO: Loop through buffer and send squares to shape_check, to
** check each square individually. Check for newlines and chars there, may be cleaner
*/

/*
** Check if char count is a multiple of 20 (for each sqaure) + 1 newline after
** each shape except last.
** Check file content for right number of . and #.
*/

int				ft_check_input(char *s)
{
	int		len;

	len = ft_strlen(s);
	if (!(((len + 1) % 21) == 0))
		return (0);
	if (!((ft_count_char(s, '#') % 4) == 0))
		return (0);
	if (!((ft_count_char(s, '.') % 12) == 0))
		return (0);
	if (!(ft_check_newline(s)))
		return (0);
	return (1);
}
