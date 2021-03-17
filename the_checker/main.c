/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:49:39 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/17 12:11:10 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
void	ft_printf_list(t_list *list, char *str);

void	init_checker(t_stacks *stacks)
{
	stacks->a = NULL;
	stacks->b = NULL;
}

t_bool	ft_malloc(void **pointer, size_t size)
{
	*pointer = malloc(size);
	if (!*pointer)
		return (false);
	return (true);
}

void	ft_error(t_stacks *stacks)
{
	write(STDERR_FILENO, "Error\n", 6);
	ft_lstclear(&stacks->a, free);
	ft_lstclear(&stacks->b, free);
	exit(1);
}

t_bool	is_statement_valid(char *line)
{
	static char instructions[NUM_OF_INSTRUCTIONS][4] = { "sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr" };
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

void handle_swap(t_stacks *stacks, char *line)
{

}

void handle_push(t_stacks *stacks, char *line)
{

}

void handle_rotate(t_stacks *stacks, char *line)
{

}

t_bool	execute_statement(t_stacks *stacks, char *line)
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
	else if (!ft_strcmp("pa", line))
		ft_lstadd_front(&stacks->a, ft_stack_pop(&stacks->b));
	else if (!ft_strcmp("pb", line))
		ft_lstadd_front(&stacks->b, ft_stack_pop(&stacks->a));
	else if (!ft_strcmp("ra", line))
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
	return (true);
}

t_bool	parse_statements(t_stacks *stacks)
{
	char	*line;
	int		gnl_ret;
	t_bool	status;
	char	*remaining;

	remaining = NULL;
	gnl_ret = 1;
	status = true;
	while (gnl_ret == 1)
	{
		gnl_ret = get_next_line(STDIN_FILENO, &line, &remaining);
		if (gnl_ret == -1)
		{
			free(line);
			free(remaining);
			return (false);
		}
		if (gnl_ret == 0)
			break;
		if (!is_statement_valid(line))
			return (false);
		status = execute_statement(stacks, line);
		ft_printf_list(stacks->a, "A");
		ft_printf_list(stacks->b, "B");
		free(line);
	}
	return (status);
}

t_bool are_stacks_sorted(t_stacks *stacks)
{
	return (is_list_sorted(stacks->a) && stacks->b == NULL);
}

#include <stdio.h>
void	ft_printf_list(t_list *list, char *str)
{
	printf("--- Stack: [%s]\n", str);
	while (list)
	{
		printf("Value: %d\n", *(int *)list->content);
		list = list->next;
	}
}

int		main(int argc, char *argv[])
{
	t_stacks stacks;

	init_checker(&stacks);
	if (argc == 1)
		return (0);
	while (argc > 1)
	{
		if (!parse_arguments(&stacks, argv[argc - 1]))
			ft_error(&stacks);
		argc--;
	}
	if (!parse_statements(&stacks))
		ft_error(&stacks);
	if (are_stacks_sorted(&stacks))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free(stacks.a);
	free(stacks.b);
	return (0);
}
