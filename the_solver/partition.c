/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:36:08 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/26 17:39:14 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		process_partition(t_push_swap *push_swap,
			t_bounds *partition, int *sorted_array)
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

t_bool		is_in_list(t_list *list, int target)
{
	while (list)
	{
		if (*(int *)list->content == target)
			return (true);
		list = list->next;
	}
	return (false);
}

int			list_find_smallest(t_list *list)
{
	int smallest;

	smallest = *(int *)list->content;
	while (list)
	{
		if (*(int *)list->content < smallest)
			smallest = *(int *)list->content;
		list = list->next;
	}
	return (smallest);
}

int			find_closest_value(t_list *list, int target, int *sorted_array)
{
	int index;

	index = 0;
	while (sorted_array[index] != target)
		index++;
	while (index >= 0)
	{
		if (is_in_list(list, sorted_array[index]))
			return (sorted_array[index]);
		index--;
	}
	return (list_find_smallest(list));
}
