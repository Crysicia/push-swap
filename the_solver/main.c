/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:12:54 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/22 17:12:35 by lpassera         ###   ########.fr       */
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

void do_sort(t_push_swap *push_swap)
{
	while (!is_list_sorted(push_swap->a) && push_swap->b != NULL)
	{

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
