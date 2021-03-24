/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:15:51 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/24 21:19:38 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void print_list(t_list *list)
{
	while (list)
	{
		printf("[%d] -> ", *(int *)list->content);
		list = list->next;
	}
	printf("END\n");
}

void print_bounds(t_bounds *bounds)
{
	printf("--- Boundaries:\nHigh: %d\nLow: %d\nNext index: %d\n", bounds->high, bounds->low, bounds->next_index);
}

void print_stacks(t_push_swap *push_swap, char *instruction)
{
	printf("--- Instruction [%3s] ---\nStack A ---\n", instruction);
	print_list(push_swap->stacks.a);
	printf("Stack B ---\n");
	print_list(push_swap->stacks.b);
	printf("\n");
}
