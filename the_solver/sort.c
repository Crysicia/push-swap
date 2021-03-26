/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:46:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/26 17:38:50 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		do_operation(t_push_swap *push_swap, char *operation, int times)
{
	int i;

	i = 0;
	if (!ft_lstaddop_back(&push_swap->statements, operation, times))
		ft_error(push_swap);
	while (++i <= times)
		execute_statement(&push_swap->stacks, operation);
}

void		sort_stack_b(t_push_swap *push_swap, t_bounds *part, int *array)
{
	int i;
	int starting_index;

	starting_index = part->starting_index;
	i = part->size;
	while (push_swap->stacks.b)
	{
		go_to_node_b(push_swap, array[starting_index + i], 0);
		do_operation(push_swap, "pa", 1);
		i--;
	}
}

void		sort_3_elements(t_push_swap *push_swap)
{
	int top;
	int mid;
	int bot;

	while (!is_list_sorted(push_swap->stacks.a))
	{
		top = *(int *)push_swap->stacks.a->content;
		mid = *(int *)push_swap->stacks.a->next->content;
		bot = *(int *)push_swap->stacks.a->next->next->content;
		if (top > mid && mid < bot && bot < top)
			do_operation(push_swap, "ra", 1);
		else if (top < mid && mid > bot && bot < top)
			do_operation(push_swap, "rra", 1);
		else
			do_operation(push_swap, "sa", 1);
	}
}

void		sort_small_stack(t_push_swap *push_swap, int *array)
{
	int stack_a_size;
	int value;
	int closest_value;
	int offset;

	stack_a_size = ft_lstsize(push_swap->stacks.a);
	if (stack_a_size == 2)
	{
		do_operation(push_swap, "sa", 1);
		return ;
	}
	do_operation(push_swap, "pb", stack_a_size - 3);
	sort_3_elements(push_swap);
	while (push_swap->stacks.b != NULL)
	{
		value = *(int *)push_swap->stacks.b->content;
		closest_value = find_closest_value(push_swap->stacks.a, value, array);
		offset = 1;
		if (closest_value > value)
			offset = 0;
		go_to_node_a(push_swap, closest_value, offset);
		do_operation(push_swap, "pa", 1);
	}
	go_to_node_a(push_swap, list_find_smallest(push_swap->stacks.a), 0);
}

void		do_sort(t_push_swap *push_swap)
{
	int			*array;
	int			arr_len;
	t_bounds	partition;

	arr_len = ft_lstsize(push_swap->stacks.a);
	array = make_array(push_swap->stacks.a, arr_len);
	if (!array)
		ft_error(push_swap);
	bubble_sort(array, arr_len);
	if (arr_len < 11)
		sort_small_stack(push_swap, array);
	else
	{
		partition.next_index = 0;
		while (partition.next_index != -1)
		{
			partition = partition_array(array, arr_len, partition.next_index);
			process_partition(push_swap, &partition, array);
			if (arr_len - 1 > partition.size)
				do_operation(push_swap, "ra", partition.size + 1);
		}
	}
	free(array);
}
