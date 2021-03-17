/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:55:10 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/17 15:55:23 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	init_checker(t_checker *checker)
{
	checker->stacks.a = NULL;
	checker->stacks.b = NULL;
	checker->statements = NULL;
}

t_bool	ft_malloc(void **pointer, size_t size)
{
	*pointer = malloc(size);
	if (!*pointer)
		return (false);
	return (true);
}

void	free_checker(t_checker *checker)
{
	ft_lstclear(&checker->stacks.a, free);
	ft_lstclear(&checker->stacks.b, free);
	ft_lstclear(&checker->statements, free);
}

void	ft_error(t_checker *checker)
{
	write(STDERR_FILENO, "Error\n", 6);
	free_checker(checker);
	exit(1);
}

t_bool	is_duplicate(char *argv[], int argc)
{
	int i;

	i = 1;
	while (i < argc - 1)
	{
		if (!ft_strcmp(argv[i], argv[argc - 1]))
			return (true);
		i++;
	}
	return (false);
}
