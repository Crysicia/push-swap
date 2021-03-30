/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:19:29 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/30 14:42:55 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shared.h"

long	ft_atol(const char *str)
{
	long long	total;
	int			sign;
	size_t		index;

	total = 0;
	sign = POSITIVE;
	index = 0;
	while ((*str >= 9 && 13 >= *str) || *str == 32)
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = NEGATIVE;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		total *= 10;
		total += str[index] - '0';
		index++;
	}
	return (total * sign);
}

t_bool	is_argument_valid(char *arg)
{
	int num_len;

	num_len = 0;
	while ((*arg >= 9 && 13 >= *arg) || *arg == 32)
		arg++;
	if (*arg == '-' || *arg == '+')
		arg++;
	while (ft_isdigit(*arg))
	{
		num_len++;
		arg++;
	}
	while ((*arg >= 9 && 13 >= *arg) || *arg == 32)
		arg++;
	return (*arg == '\0' && num_len <= 10 && num_len > 0);
}

t_bool	parse_arguments(t_stacks *stacks, char *arg)
{
	long	temp;
	int		*value;
	t_list	*node;

	if (!is_argument_valid(arg) || !ft_malloc((void **)&value, sizeof(int)))
		return (false);
	temp = ft_atol(arg);
	*value = (int)temp;
	node = ft_lstnew(value);
	if (temp > INT_MAX || temp < INT_MIN || !node)
	{
		free(value);
		return (false);
	}
	ft_lstadd_front(&(stacks->a), node);
	return (true);
}

t_bool	set_argument(t_args *args, char *line)
{
	if (!ft_strcmp(line, "-v"))
	{
		if (args->verbose)
			return (false);
		args->verbose = true;
		return (true);
	}
	return (false);
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
