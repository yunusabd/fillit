/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsalai <vsalai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:21:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/15 18:44:14 by vsalai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "./libft/libft.h"

#define LINE s[i][4]
#define X s[i][5]

typedef unsigned int uint;

unsigned int	read_shape(char *s);
char			*read_file(char *file);
int				check_input(char *s);
void			input_to_array(char *s, unsigned int **dst, int shapes);
void			compare_shapes(unsigned int **shapes, int n);
void			shift_array(unsigned int *arr, int spaces, int size);
void			fillit(unsigned int **arr, int *gridsize, int shapes);
int				shift_back(unsigned int *shape);
char			**print_shapes(uint **s, int *gridsize, int shapes);
int				shape_height(uint *s);
void            toggle_shape(uint *shape, uint **map);

#endif
