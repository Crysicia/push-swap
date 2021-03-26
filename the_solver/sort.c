/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:46:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/26 15:41:03 by lpassera         ###   ########.fr       */
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

void		sort_stack_b(t_push_swap *push_swap, t_bounds *partition, int *sorted_array)
{
	int i;
	int starting_index;

	starting_index = partition->starting_index;
	i = partition->size;
	while (push_swap->stacks.b)
	{
		go_to_node_b(push_swap, sorted_array[starting_index + i], 0);
		do_operation(push_swap, "pa", 1);
		i--;
	}
}

void		process_partition(t_push_swap *push_swap, t_bounds *partition, int *sorted_array)
{
	int i;

	i = 0;
	while (i <= partition->size)
	{
		go_to_range_a(push_swap, partition);
		do_operation(push_swap, "pb", 1);
		i++;
	}
	if (partition->starting_index > 0)
		go_to_node_a(push_swap, sorted_array[partition->starting_index - 1], 1);
	sort_stack_b(push_swap, partition, sorted_array);
}

t_bounds	partition_array(int *sorted_array, int size, int min_index)
{
	t_bounds	bounds;
	int			partition_size;
	int			next_index;

	partition_size = size / 10;
	if (size < 250)
		partition_size = 20;
	if (size - min_index - 1 < partition_size)
		partition_size = size - min_index - 1;
	next_index = min_index + partition_size + 1;
	if (next_index >= size)
		next_index = -1;
	bounds.low = sorted_array[min_index];
	bounds.high = sorted_array[min_index + partition_size];
	bounds.next_index = next_index;
	bounds.starting_index = min_index;
	bounds.size = partition_size;
	return (bounds);
}

int find_closest_value(t_list *list, int target)
{
	int closest;

	closest = INT_MAX;
	while (list)
	{
		if (ft_abs(target - *(int *)list->content) < ft_abs(closest - *(int *)list->content))
			closest = *(int *)list->content;
		list = list->next;
	}
	return (closest);
}

void sort_3_elements(t_push_swap *push_swap)
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

void sort_small_stack(t_push_swap *push_swap)
{
	int stack_a_size;
	int current_value;
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
		offset = 1;
		current_value = *(int *)push_swap->stacks.b->content;
		closest_value = find_closest_value(push_swap->stacks.a, current_value);
		if (closest_value < current_value)
			offset = 0;
		go_to_node_a(push_swap, closest_value, offset);
		do_operation(push_swap, "pa", 1);
	}
}

int *make_array(t_list *list, int size)
{
	int *sorted_array;
	int i;

	i = 0;
	sorted_array = malloc(size * sizeof(int));
	if (!sorted_array)
		return (NULL);
	while (list)
	{
		sorted_array[i] = *(int *)list->content;
		list = list->next;
		i++;
	}
	return (sorted_array);
}

void		do_sort(t_push_swap *push_swap)
{
	int			*sorted_array;
	int			arr_len;
	t_bounds	partition;

	arr_len = ft_lstsize(push_swap->stacks.a);
	if (arr_len < 11)
	{
		sort_small_stack(push_swap);
		return ;
	}
	sorted_array = make_array(push_swap->stacks.a, arr_len);
	if (!sorted_array)
		ft_error(push_swap);
	bubble_sort(sorted_array, arr_len);
	partition.next_index = 0;
	while (partition.next_index != -1)
	{
		partition = partition_array(sorted_array, arr_len, partition.next_index);
		process_partition(push_swap, &partition, sorted_array);
		if (arr_len - 1> partition.size)
			do_operation(push_swap, "ra", partition.size + 1);
	}
	free(sorted_array);
}
