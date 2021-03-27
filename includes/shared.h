/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:38:02 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/27 17:50:45 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H
# include <limits.h>
# include "types.h"
# include "../libft/libft.h"

t_bool	parse_arguments(t_stacks *stacks, char *arg);
t_bool	ft_malloc(void **pointer, size_t size);
t_bool	is_duplicate(char *argv[], int argc);

void	init_push_swap(t_push_swap *push_swap);
void	free_push_swap(t_push_swap *push_swap);
void	ft_error(t_push_swap *push_swap);

void	handle_swap(t_stacks *stacks, char *line);
void	handle_push(t_stacks *stacks, char *line);
void	handle_rotate(t_stacks *stacks, char *line);
void	execute_statement(t_stacks *stacks, char *line);
void	execute_statements(t_push_swap *push_swap, t_args *args);

/*
** Stacks
*/
void	ft_stack_rotate(t_list **stack);
void	ft_stack_reverse_rotate(t_list **stack);
void	ft_stack_swap(t_list **stack);
t_list	*ft_stack_pop(t_list **stack);
t_bool	is_list_sorted(t_list *list);

#endif
