/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:19:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/13 15:23:20 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/types.h"
#include "checker.h"

t_bool is_argument_valid(char *arg)
{
	while ((*arg >= 9 && 13 >= *arg) || *arg == 32)
		arg++;
	if (*arg == '-' || *arg == '+')
		arg++;
	while (ft_isdigit(*arg))
		arg++;
	while ((*arg >= 9 && 13 >= *arg) || *arg == 32)
		arg++;
	return (*arg == '\0');
}

// TODO: Need to check for duplicates
// TODO: Need to check for overflowing numbers
t_bool parse_arguments(t_stacks *stacks, char *arg)
{
	int *value;
	t_list *node;

	if (!is_argument_valid(arg) || !ft_malloc((void **)&value, sizeof(int)))
		return (false);
	*value = ft_atoi(arg);
	node = ft_lstnew(value);
	if (!node)
	{
		free(value);
		return (false);
	}
	ft_lstadd_front(&(stacks->a), node);
	return (true);
}
