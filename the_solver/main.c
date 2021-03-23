/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:12:54 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/23 12:45:58 by lpassera         ###   ########.fr       */
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

#include <stdio.h>
#define PARTITION_SIZE 5

typedef struct s_bounds
{
	int high;
	int low;
	int next_index;
}				t_bounds;

void print_bounds(t_bounds *bounds)
{
	printf("--- Boundaries:\nHigh: %d\nLow: %d\nNext index: %d\n", bounds->high, bounds->low, bounds->next_index);
}

void process_partition(t_push_swap *push_swap, t_bounds *partition)
{
	t_list *node;
	int rotate_distance;
	int best_distance;
	int reverse_rotate_distance;
	int size;

	rotate_distance = 0;
	best_distance = 0;
	node = push_swap->stacks.a;
	size = ft_lstsize(node);
	while (node)
	{
		if (ft_in_range(partition->low, partition->high, *(int *)node->content))
		{
			if (rotate_distance < best_distance || size - rotate_distance < reverse_rotate_distance)
			{
				best_distance = rotate_distance;
				reverse_rotate_distance = size - rotate_distance;
			}
		}
		node = node->next;
		rotate_distance++;
	}
	printf("best distance: %d\nBest reverse_rotate_distance: %d\n", best_distance, reverse_rotate_distance);
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
		print_bounds(&partition);
		process_partition(push_swap, &partition);
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
