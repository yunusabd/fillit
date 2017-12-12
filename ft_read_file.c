/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:03:25 by vsalai            #+#    #+#             */
/*   Updated: 2017/12/11 16:26:29 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>

char	*ft_read_file(char *file)
{
	char	*buf;
	int		fd;

	buf = (char *)malloc(sizeof(*buf) * ((26 * 21) - 1));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	read(fd, buf, (sizeof(*buf) * ((26 * 21) - 1)));
	close(fd);
	return (buf);
}
