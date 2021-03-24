/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:12:54 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/24 22:55:24 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void print_instructions(t_push_swap *push_swap)
{
	ft_lstiter(push_swap->statements, ft_putendl);
}

void do_operation(t_push_swap *push_swap, char *operation, int times)
{
	int i;

	i = 0;
	if (!ft_lstaddop_back(&push_swap->statements, operation, times))
		ft_error(push_swap);
	while (++i <= times)
		execute_statement(&push_swap->stacks, operation);
}

int get_node_distance(t_list *list, t_bounds *partition)
{
	int rotate_distance;
	int best_distance;
	int reverse_rotate_distance;
	int size;

	rotate_distance = 0;
	reverse_rotate_distance = INT_MAX;
	best_distance = INT_MAX;
	size = ft_lstsize(list);
	while (list)
	{
		if (ft_in_range(partition->low, partition->high, *(int *)list->content))
		{
			if (rotate_distance < best_distance)
				best_distance = rotate_distance;
			if ((size - rotate_distance) < reverse_rotate_distance)
				reverse_rotate_distance = ft_max(size - rotate_distance, 0);
		}
		list = list->next;
		rotate_distance++;
	}
	if (reverse_rotate_distance < best_distance)
		return (-reverse_rotate_distance);
	return (best_distance);
}

int get_int_distance(t_list *list, int value)
{
	int rotate_distance;
	int size;

	rotate_distance = 0;
	size = ft_lstsize(list);
	while (list)
	{
		if (value == *(int *)list->content)
		{
			if ((size - rotate_distance) < rotate_distance)
				return (-(size - rotate_distance));
			return (rotate_distance);
		}
		list = list->next;
		rotate_distance++;
	}
	return (rotate_distance);
}

void sort_stack_b(t_push_swap *push_swap, t_bounds *partition, int *sorted_array)
{
	int node_distance;
	int i;
	int starting_index;

	starting_index = partition->starting_index;
	i = partition->size;
	while (push_swap->stacks.b)
	{
		node_distance = get_int_distance(push_swap->stacks.b, sorted_array[starting_index + i]);
		if (node_distance < 0)
			do_operation(push_swap, "rrb", ft_abs(node_distance));
		else
			do_operation(push_swap, "rb", node_distance);
		do_operation(push_swap, "pa", 1);
		i--;
	}
}


void process_partition(t_push_swap *push_swap, t_bounds *partition, int *sorted_array)
{
	int node_distance;
	int i;

	i = 0;
	while (i <= partition->size)
	{
		node_distance = get_node_distance(push_swap->stacks.a, partition);
		if (node_distance < 0)
			do_operation(push_swap, "rra", ft_abs(node_distance));
		else
			do_operation(push_swap, "ra", node_distance);
		do_operation(push_swap, "pb", 1);
		i++;
	}
	if (partition->starting_index > 0)
	{
		node_distance = get_int_distance(push_swap->stacks.a, sorted_array[partition->starting_index - 1]);
		if (node_distance < 0)
			do_operation(push_swap, "rra", ft_abs(node_distance) - 1);
		else
			do_operation(push_swap, "ra", node_distance + 1);
	}
	sort_stack_b(push_swap, partition, sorted_array);
}

t_bounds partition_array(int *sorted_array, int size, int min_index)
{
	t_bounds bounds;
	int partition_size;
	int next_index;

	if (size < 250)
		partition_size = 20;
	else
		partition_size = size / 10;
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

void do_sort(t_push_swap *push_swap)
{
	int *sorted_array;
	int array_length;
	t_list *node;
	int i;

	i = 0;
	node = push_swap->stacks.a;
	array_length = ft_lstsize(push_swap->stacks.a);
	sorted_array = malloc(array_length * sizeof(int));
	while (node)
	{
		sorted_array[i] = *(int *)node->content;
		node = node->next;
		i++;
	}
	bubble_sort(sorted_array, array_length);
	t_bounds partition;
	partition.next_index = 0;
	while (partition.next_index != -1)
	{
		partition = partition_array(sorted_array, array_length, partition.next_index);
		process_partition(push_swap, &partition, sorted_array);
		do_operation(push_swap, "ra", partition.size + 1);
	}
	return ;
}


int		main(int argc, char *argv[])
{
	t_push_swap push_swap;

	init_push_swap(&push_swap);
	if (argc == 1)
		return (0);
	while (argc > 1)
	{
		if (is_duplicate(argv, argc)
			|| !parse_arguments(&push_swap.stacks, argv[argc - 1]))
			ft_error(&push_swap);
		argc--;
	}
	do_sort(&push_swap);
	print_instructions(&push_swap);
	free_push_swap(&push_swap);
	return (0);
}
