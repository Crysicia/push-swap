/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:55:10 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/19 16:45:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	init_push_swap(t_push_swap *push_swap)
{
	push_swap->stacks.a = NULL;
	push_swap->stacks.b = NULL;
	push_swap->statements = NULL;
}

t_bool	ft_malloc(void **pointer, size_t size)
{
	*pointer = malloc(size);
	if (!*pointer)
		return (false);
	return (true);
}

void	free_push_swap(t_push_swap *push_swap)
{
	ft_lstclear(&push_swap->stacks.a, free);
	ft_lstclear(&push_swap->stacks.b, free);
	ft_lstclear(&push_swap->statements, free);
}

void	ft_error(t_push_swap *push_swap)
{
	write(STDERR_FILENO, "Error\n", 6);
	free_push_swap(push_swap);
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
