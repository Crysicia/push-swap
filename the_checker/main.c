/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:49:39 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/26 17:43:40 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_bool	is_statement_valid(char *line)
{
	static char instructions[NUM_OF_INSTRUCTIONS][4] = {"sa", "sb", "ss",
														"pa", "pb", "ra",
														"rb", "rr", "rra",
														"rrb", "rrr" };
	int			i;

	i = 0;
	while (i < NUM_OF_INSTRUCTIONS)
	{
		if (!ft_strcmp(line, instructions[i]))
			return (true);
		i++;
	}
	return (false);
}

t_bool	parse_statements(t_push_swap *push_swap)
{
	char	*line;
	int		gnl_ret;
	char	*remaining;
	t_list	*node;

	remaining = NULL;
	gnl_ret = 1;
	while (gnl_ret == 1)
	{
		line = NULL;
		gnl_ret = get_next_line(STDIN_FILENO, &line, &remaining);
		if (gnl_ret == -1)
		{
			free(line);
			free(remaining);
			return (false);
		}
		if (gnl_ret == 0)
			break ;
		node = ft_lstnew(line);
		if (!node || !is_statement_valid(line))
			return (false);
		ft_lstadd_back(&push_swap->statements, node);
	}
	return (true);
}

t_bool	are_stacks_sorted(t_stacks *stacks)
{
	return (is_list_sorted(stacks->a) && stacks->b == NULL);
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
	if (!parse_statements(&push_swap))
		ft_error(&push_swap);
	execute_statements(&push_swap);
	if (are_stacks_sorted(&push_swap.stacks))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_push_swap(&push_swap);
	return (0);
}
