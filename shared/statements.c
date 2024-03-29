/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:30:06 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/30 10:30:31 by lpassera         ###   ########.fr       */
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

void	execute_statements(t_push_swap *push_swap, t_args *args)
{
	t_list *node;

	node = push_swap->statements;
	while (node)
	{
		execute_statement(&push_swap->stacks, node->content);
		if (args->verbose)
			display_stacks(push_swap, node->content);
		node = node->next;
	}
}
