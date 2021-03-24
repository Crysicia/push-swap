/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:12:07 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/24 22:10:37 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H
# include "../includes/shared.h"
# include "debug.h"

void ft_putendl(void *ptr);
int ft_abs(int i);
void bubble_sort(int *arr, int size);
t_bool	ft_lstaddop_back(t_list **lst, char *operation, int times);

#endif
