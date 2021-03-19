/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:38:02 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/19 16:46:44 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H
# include <limits.h>
# include "types.h"
# include "../libft/libft.h"

t_bool	parse_arguments(t_stacks *stacks, char *arg);
t_bool	ft_malloc(void **pointer, size_t size);
t_bool	is_duplicate(char *argv[], int argc);;

void	init_push_swap(t_push_swap *push_swap);
void	free_push_swap(t_push_swap *push_swap);
void	ft_error(t_push_swap *push_swap);
#endif
