/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:49:39 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/13 15:47:36 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/types.h"
#include "checker.h"

void init_checker(t_stacks *stacks)
{
	stacks->a = NULL;
	stacks->b = NULL;
}

t_bool ft_malloc(void **pointer, size_t size)
{
	*pointer = malloc(size);
	if (*pointer == NULL)
		return (false);
	return (true);
}

void ft_error(t_stacks *stacks)
{
	write(STDERR_FILENO, "Error\n", 6);
	ft_lstclear(&stacks->a, free);
	ft_lstclear(&stacks->b, free);
	exit(1);
}

t_bool execute_statements(t_stacks *stacks)
{
	char	*line;
	int		gnl_ret;
	t_bool	status;

	gnl_ret = 1;
	while (gnl_ret == 1)
	{
		gnl_ret = get_next_line(STDIN_FILENO, &line, &game->gnl_remaining);
		if (gnl_ret == -1)
			return (set_error(error, READ_ERROR));
		if (!line_is_blank(line))
			*error = parse_setting(game, line);
		free(line);
	}
	return (status);
}

#include <stdio.h>
void ft_printf_list(t_list *list)
{
	while (list)
	{
		printf("Value: %d\n", *(int *)list->content);
		list = list->next;
	}
}

int main(int argc, char *argv[])
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
	if (!execute_statements(&stacks))
		ft_error(&stacks);
	return (0);
}
