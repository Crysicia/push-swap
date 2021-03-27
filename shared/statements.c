/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:30:06 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/27 14:40:32 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shared.h"

void	handle_swap(t_stacks *stacks, char *line)
{
	if (!ft_strcmp("sa", line))
		ft_stack_swap(&stacks->a);
	else if (!ft_strcmp("sb", line))
		ft_stack_swap(&stacks->b);
	else if (!ft_strcmp("ss", line))
	{
		ft_stack_swap(&stacks->a);
		ft_stack_swap(&stacks->b);
	}
}

void	handle_push(t_stacks *stacks, char *line)
{
	if (!ft_strcmp("pa", line))
		ft_lstadd_front(&stacks->a, ft_stack_pop(&stacks->b));
	else if (!ft_strcmp("pb", line))
		ft_lstadd_front(&stacks->b, ft_stack_pop(&stacks->a));
}

void	handle_rotate(t_stacks *stacks, char *line)
{
	if (!ft_strcmp("ra", line))
		ft_stack_rotate(&stacks->a);
	else if (!ft_strcmp("rb", line))
		ft_stack_rotate(&stacks->b);
	else if (!ft_strcmp("rr", line))
	{
		ft_stack_rotate(&stacks->a);
		ft_stack_rotate(&stacks->b);
	}
	else if (!ft_strcmp("rra", line))
		ft_stack_reverse_rotate(&stacks->a);
	else if (!ft_strcmp("rrb", line))
		ft_stack_reverse_rotate(&stacks->b);
	else if (!ft_strcmp("rrr", line))
	{
		ft_stack_reverse_rotate(&stacks->a);
		ft_stack_reverse_rotate(&stacks->b);
	}
}

void	execute_statement(t_stacks *stacks, char *line)
{
	if (*line == 's')
		handle_swap(stacks, line);
	else if (*line == 'p')
		handle_push(stacks, line);
	else if (*line == 'r')
		handle_rotate(stacks, line);
}

#include <stdio.h>

void display_stacks(t_push_swap *push_swap, char *line)
{
	t_list *stack_a;
	t_list *stack_b;
	int stack_a_size;
	int stack_b_size;
	int biggest_stack;

	stack_a_size = ft_lstsize(push_swap->stacks.a);
	stack_b_size = ft_lstsize(push_swap->stacks.b);
	biggest_stack = ft_max(stack_a_size, stack_b_size);
	stack_a = push_swap->stacks.a;
	stack_b = push_swap->stacks.b;
	printf("--- Current instruction [%3s] ---\n", line);
	while (biggest_stack > 0)
	{
		if (stack_a_size > stack_b_size)
		{
			printf("%15d | %15.0d\n", *(int *)stack_a->content, 0);
			stack_a_size--;
			stack_a = stack_a->next;
		}
		else if (stack_a_size < stack_b_size)
		{
			printf("%15.0d | %15d\n", 0, *(int *)stack_b->content);
			stack_b_size--;
			stack_b = stack_b->next;
		}
		else
		{
			printf("%15d | %15d\n", *(int *)stack_a->content, *(int *)stack_b->content);
			stack_a = stack_a->next;
			stack_b = stack_b->next;
		}
		biggest_stack--;
	}
	printf("--- Stack A ----|---- Stack B ---\n\n");
}


void	execute_statements(t_push_swap *push_swap)
{
	t_list *node;

	node = push_swap->statements;
	while (node)
	{
		execute_statement(&push_swap->stacks, node->content);
		display_stacks(push_swap, node->content);
		node = node->next;
	}
}
