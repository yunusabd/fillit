/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 13:21:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/14 13:58:35 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "./libft/libft.h"
#include <stdio.h>

#define LINE s[i][4]

typedef unsigned int uint;

unsigned int	ft_read_shape(char *s);
char			*ft_read_file(char *file);
int				ft_check_input(char *s);
void			ft_input_to_array(char *s, unsigned int **dst, int shapes);
void			ft_compare_shapes(unsigned int **shapes, int n);
void			ft_shift_array(unsigned int *arr, int spaces, int size);
void			fillit(unsigned int **arr, int *gridsize, int shapes);
int				ft_shift_back(unsigned int *shape);

#endif
