/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:19:46 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/30 14:43:01 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/shared.h"

void	display_stack_a(t_display *display)
{
	printf("%15d |\n", *(int *)display->stack_a->content);
	display->stack_a = display->stack_a->next;
	display->stack_a_size--;
}

void	display_stack_b(t_display *display)
{
	printf("%15.0d | %15d\n", 0, *(int *)display->stack_b->content);
	display->stack_b = display->stack_b->next;
	display->stack_b_size--;
}

void	display_both_stacks(t_display *display)
{
	printf("%15d | %15d\n",
		*(int *)display->stack_a->content,
		*(int *)display->stack_b->content);
	display->stack_a = display->stack_a->next;
	display->stack_b = display->stack_b->next;
}

void	display_row(t_display *display)
{
	if (display->stack_a_size > display->stack_b_size)
		display_stack_a(display);
	else if (display->stack_a_size < display->stack_b_size)
		display_stack_b(display);
	else
		display_both_stacks(display);
}

void	display_stacks(t_push_swap *push_swap, char *line)
{
	t_display display;

	display.stack_a = push_swap->stacks.a;
	display.stack_b = push_swap->stacks.b;
	display.stack_a_size = ft_lstsize(push_swap->stacks.a);
	display.stack_b_size = ft_lstsize(push_swap->stacks.b);
	display.biggest_stack = ft_max(display.stack_a_size, display.stack_b_size);
	printf("--- Current instruction [%3s] ---\n", line);
	while (display.biggest_stack > 0)
	{
		display_row(&display);
		display.biggest_stack--;
	}
	printf("--- Stack A ----|---- Stack B ---\n\n");
}
