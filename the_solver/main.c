/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:12:54 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/23 17:28:47 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shared.h"

void ft_putendl(void *ptr)
{
	char *str;

	str = (char *)ptr;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void print_instructions(t_push_swap *push_swap)
{
	ft_lstiter(push_swap->statements, ft_putendl);
}

void bubble_sort(int *arr, int size)
{
	t_bool swapped;
	int i;
	int temp;

	swapped = true;
	while (swapped)
	{
		i = 0;
		swapped = false;
		while (i + 1 < size)
		{
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = temp;
				swapped = true;
			}
			i++;
		}
		size--;
	}
}


int ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}
#include <stdio.h>
#define PARTITION_SIZE 5

typedef struct s_bounds
{
	int high;
	int low;
	int next_index;
	int size;
}				t_bounds;

void print_bounds(t_bounds *bounds)
{
	printf("--- Boundaries:\nHigh: %d\nLow: %d\nNext index: %d\n", bounds->high, bounds->low, bounds->next_index);
}

void execute_rra(t_push_swap *push_swap, int times)
{
	int i;

	i = 0;
	while (i < times)
	{
		ft_lstadd_back(&push_swap->statements, ft_lstnew(ft_strdup("rra")));
		ft_stack_reverse_rotate(&push_swap->stacks.a);
		i++;
	}
}

void execute_ra(t_push_swap *push_swap, int times)
{
	int i;

	i = 0;
	while (i < times)
	{
		ft_lstadd_back(&push_swap->statements, ft_lstnew(ft_strdup("ra")));
		ft_stack_rotate(&push_swap->stacks.a);
		i++;
	}
}

void execute_pb(t_push_swap *push_swap, int times)
{
	int i;

	i = 0;
	while (i < times)
	{
		ft_lstadd_back(&push_swap->statements, ft_lstnew(ft_strdup("pb")));
		ft_lstadd_front(&push_swap->stacks.b, ft_stack_pop(&push_swap->stacks.a));
		i++;
	}
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

void process_partition(t_push_swap *push_swap, t_bounds *partition)
{
	int node_distance;
	int i;

	i = 0;
	while (i <= partition->size)
	{
		node_distance = get_node_distance(push_swap->stacks.a, partition);
		// printf("Distance: %d\n", node_distance);
		if (node_distance < 0)
			execute_rra(push_swap, ft_abs(node_distance));
		else
			execute_ra(push_swap, node_distance);
		execute_pb(push_swap, 1);
		i++;
	}
}

t_bounds partition_array(int *sorted_array, int size, int min_index)
{
	t_bounds bounds;
	int partition_size;
	int next_index;

	partition_size = PARTITION_SIZE;
	if (size - min_index - 1 < 5)
		partition_size = size - min_index - 1;
	next_index = min_index + partition_size + 1;
	if (next_index >= size)
		next_index = -1;
	bounds.low = sorted_array[min_index];
	bounds.high = sorted_array[min_index + partition_size];
	bounds.next_index = next_index;
	bounds.size = partition_size;
	return (bounds);
}

void print_list(t_list *list)
{
	while (list)
	{
		printf("[%d] -> ", *(int *)list->content);
		list = list->next;
	}
	printf("END\n");
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
		// print_bounds(&partition);
		process_partition(push_swap, &partition);
		printf("Stack A ---\n");
		print_list(push_swap->stacks.a);
		printf("Stack B ---\n");
		print_list(push_swap->stacks.b);
	}

	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("sa")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("rr")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("rra")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("rrb")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("sb")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("ss")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("ra")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("rb")));
	// ft_lstadd_front(&push_swap->statements, ft_lstnew(ft_strdup("rrr")));
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


// Scan the A stack for biggest and smallest integers
// Sort the stack A in an array
// Divide the array in buckets of N integers
// Get the integers from the first bucket and push them to stack B
// 	Sort the b stack
// 	Push the b stack to a
// 	repeat
