/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:09:06 by yabdulha          #+#    #+#             */
/*   Updated: 2017/12/14 22:26:09 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* take as input: array of ints, number of shapes
** 
** shift shapes until [other shapes] & [shape] = 0
*/

unsigned int		*ft_create_map()
{
	int				i;
	unsigned int	*arr;

	arr = (unsigned int*)malloc(sizeof(*arr) * (sizeof(*arr) * 8));
	printf("sizeof(*arr) * 8\n", sizeof(*arr) * 8);
	i= 0;
	while (i < (sizeof(*arr) * 8 + 1))
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}



int				ft_put_shapes(unsigned int **arr, unsigned int *map, int shapes, int gridsize)
{
	int				i;
	int				j;
	int				k;
	int				l;
	int				shifted;

	i = 0;
	while (i < (gridsize * gridsize))
	{
		shifted = 0;
		while (j < (sizeof))
		{
			if ((arr[i][j] & map[i][j]) == 0)
				// free spot found
			else
				// try shifting arr>>1 
				// if the [shifted] variable is greater than gridsize, try j + 1 aka the next line of the map
			{
				if (!(arr[i] & 1 | arr[i]))


		}
		if ()
