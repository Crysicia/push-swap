/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:54:03 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/19 16:45:47 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_stack_rotate(t_list **stack)
{
	t_list *node;

	node = *stack;
	if (!node)
		return ;
	*stack = node->next;
	node->next = NULL;
	ft_lstadd_back(stack, node);
}

void	ft_stack_reverse_rotate(t_list **stack)
{
	t_list *node;
	t_list *previous;

	node = *stack;
	previous = NULL;
	if (!node)
		return ;
	while (node->next)
	{
		previous = node;
		node = node->next;
	}
	if (!previous)
		return ;
	node->next = *stack;
	*stack = node;
	previous->next = NULL;
}

void	ft_stack_swap(t_list **stack)
{
	t_list *node;
	t_list *next;

	node = *stack;
	if (!node)
		return ;
	next = node->next;
	if (!next)
		return ;
	node->next = next->next;
	next->next = node;
	*stack = next;
}

t_list	*ft_stack_pop(t_list **stack)
{
	t_list *node;

	node = *stack;
	if (!node)
		return (NULL);
	*stack = node->next;
	node->next = NULL;
	return (node);
}

t_bool	is_list_sorted(t_list *list)
{
	while (list->next)
	{
		if (*(int *)list->content > *(int *)list->next->content)
			return (false);
		list = list->next;
	}
	return (true);
}
