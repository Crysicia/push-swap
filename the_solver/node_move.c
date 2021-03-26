/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:44:33 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/26 17:33:16 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

int		get_node_distance(t_list *list, t_bounds *partition)
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

int		get_int_distance(t_list *list, int value)
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

void	go_to_node_b(t_push_swap *push_swap, int target, int offset)
{
	int node_distance;

	node_distance = get_int_distance(push_swap->stacks.b, target);
	if (node_distance < 0)
		do_operation(push_swap, "rrb", ft_abs(node_distance) - offset);
	else
		do_operation(push_swap, "rb", node_distance + offset);
}

void	go_to_node_a(t_push_swap *push_swap, int target, int offset)
{
	int node_distance;

	node_distance = get_int_distance(push_swap->stacks.a, target);
	if (node_distance < 0)
		do_operation(push_swap, "rra", ft_abs(node_distance) - offset);
	else
		do_operation(push_swap, "ra", node_distance + offset);
}

void	go_to_range_a(t_push_swap *push_swap, t_bounds *partition)
{
	int node_distance;

	node_distance = get_node_distance(push_swap->stacks.a, partition);
	if (node_distance < 0)
		do_operation(push_swap, "rra", ft_abs(node_distance));
	else
		do_operation(push_swap, "ra", node_distance);
}
