/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:13:30 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/24 22:09:21 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void	ft_putendl(void *ptr)
{
	char	*str;

	str = (char *)ptr;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

int		ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	bubble_sort(int *arr, int size)
{
	t_bool	swapped;
	int		i;
	int		temp;

	swapped = true;
	while (swapped)
	{
		i = 0;
		swapped = false;
		while (i + 1 < size)
		{
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = temp;
				swapped = true;
			}
			i++;
		}
		size--;
	}
}

t_bool	ft_lstaddop_back(t_list **lst, char *operation, int times)
{
	t_list *node;
	char *str;
	int i;

	i = 0;
	while (i < times)
	{
		str = NULL;
		node = NULL;
		str = ft_strdup(operation);
		if (!str)
			return (false);
		node = ft_lstnew(str);
		if (!node)
		{
			free(str);
			return (false);
		}
		ft_lstadd_back(lst, node);
		i++;
	}
	return (true);
}
