/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:46:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/25 16:20:29 by lpassera         ###   ########.fr       */
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
