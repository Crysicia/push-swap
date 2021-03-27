/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:49:39 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/27 17:50:33 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

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

t_bool	free_gnl(t_list *node, char *remaining, char *line)
{
	free(remaining);
	free(line);
	free(node);
	return (false);
}

t_bool	parse_statements(t_push_swap *push_swap)
{
	char	*line;
	int		gnl_ret;
	char	*remaining;
	t_list	*node;

	remaining = NULL;
	node = NULL;
	gnl_ret = 1;
	while (gnl_ret == 1)
	{
		line = NULL;
		gnl_ret = get_next_line(STDIN_FILENO, &line, &remaining);
		if (gnl_ret == -1)
			return (free_gnl(node, remaining, line));
		if (gnl_ret == 0)
			break ;
		node = ft_lstnew(line);
		if (!node || !is_statement_valid(line))
			return (free_gnl(node, remaining, line));
		ft_lstadd_back(&push_swap->statements, node);
	}
	free(line);
	return (true);
}

t_bool	are_stacks_sorted(t_stacks *stacks)
{
	return (is_list_sorted(stacks->a) && stacks->b == NULL);
}

t_bool	set_argument(t_args *args, char *line)
{
	if (!ft_strcmp(line, "-c"))
	{
		if (args->color)
			return (false);
		args->color = true;
	}
	else if (!ft_strcmp(line, "-v"))
	{
		if (args->verbose)
			return (false);
		args->verbose = true;
	}
	else
		return (false);
	return (true);
}

void	parse_bonus_arguments(int argc, char *argv[], t_args *args)
{
	t_bool	parsing;
	int		i;

	i = 0;
	args->color = false;
	args->verbose = false;
	parsing = true;
	while (parsing && ++i < argc)
		parsing = set_argument(args, argv[i]);
	args->index = i;
}

int		main(int argc, char *argv[])
{
	t_push_swap push_swap;
	t_args		args;

	init_push_swap(&push_swap);
	if (argc == 1)
		return (0);
	parse_bonus_arguments(argc, argv, &args);
	while (argc > args.index)
	{
		if (is_duplicate(argv, argc)
			|| !parse_arguments(&push_swap.stacks, argv[argc - 1]))
			ft_error(&push_swap);
		argc--;
	}
	if (!parse_statements(&push_swap))
		ft_error(&push_swap);
	execute_statements(&push_swap, &args);
	if (are_stacks_sorted(&push_swap.stacks))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_push_swap(&push_swap);
	return (0);
}
