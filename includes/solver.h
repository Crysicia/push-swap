/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:12:07 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/30 16:16:59 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H
# include "shared.h"

void		process_partition(t_push_swap *push_swap, t_bounds *partition,
			int *sorted_array);
t_bounds	partition_array(int *sorted_array, int size, int min_index);
t_bool		is_in_list(t_list *list, int target);
int			list_find_smallest(t_list *list);
int			find_closest_value(t_list *list, int target, int *sorted_array);
int			*make_array(t_list *list, int size);
void		ft_putendl(void *ptr);
int			ft_abs(int i);
void		bubble_sort(int *arr, int size);
t_bool		ft_lstaddop_back(t_list **lst, char *operation, int times);
int			get_node_distance(t_list *list, t_bounds *partition);
int			get_int_distance(t_list *list, int value);
void		go_to_node_b(t_push_swap *push_swap, int target, int offset);
void		go_to_node_a(t_push_swap *push_swap, int target, int offset);
void		go_to_range_a(t_push_swap *push_swap, t_bounds *partition);
void		do_operation(t_push_swap *push_swap, char *operation, int times);
void		sort_stack_b(t_push_swap *push_swap, t_bounds *partition,
			int *sorted_array);
void		process_partition(t_push_swap *push_swap, t_bounds *partition,
			int *sorted_array);
t_bounds	partition_array(int *sorted_array, int size, int min_index);
void		do_sort(t_push_swap *push_swap);
#endif
