/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:03:25 by vsalai            #+#    #+#             */
/*   Updated: 2018/04/15 17:29:35 by vsalai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>

char	*ft_read_file(char *file)
{
	char	*buf;
	int		fd;

	buf = (char *)malloc(sizeof(*buf) * (26 * 21));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	read(fd, buf, (sizeof(*buf) * ((26 * 21))));
	close(fd);
	return (buf);
}
