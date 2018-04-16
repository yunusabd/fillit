/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:21:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/16 21:50:19 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "./libft/libft.h"
# include <fcntl.h>

# define X s[i][4]
# define Y s[i][5]

typedef unsigned int	t_uint;

void			print_error(void);
char			*read_file(char *file);
int				check_input(char *s);
void			input_to_array(char *s, unsigned int **dst, int shapes);
int				compare_shapes(unsigned int **shapes, int n);
void			shift_array(unsigned int *arr, int spaces, int size);
void			fillit(unsigned int **arr, int gridsize, int shapes);
int				shift_back(unsigned int *shape);
char			**print_shapes(t_uint **s, int gridsize, int shapes);
int				shape_height(t_uint *s);
void			toggle_shape(t_uint *shape, t_uint **map);
int				increase_gridsize(t_uint **s, t_uint *m, int i, int *gridsize);

#endif
