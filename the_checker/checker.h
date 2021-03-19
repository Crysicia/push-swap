/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:03:56 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/19 13:47:53 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "../libft/libft.h"
# include "../includes/types.h"
# include <limits.h>
# define NUM_OF_INSTRUCTIONS 11
# define BUFFER_SIZE 256

t_bool	parse_arguments(t_stacks *stacks, char *arg);
void	execute_statements(t_checker *checker);

/*
** Stacks
*/
void	ft_stack_rotate(t_list **stack);
void	ft_stack_reverse_rotate(t_list **stack);
void	ft_stack_swap(t_list **stack);
t_list	*ft_stack_pop(t_list **stack);
t_bool	is_list_sorted(t_list *list);

/*
** Utils
*/
t_bool	ft_malloc(void **pointer, size_t size);
void	init_checker(t_checker *checker);
void	free_checker(t_checker *checker);
void	ft_error(t_checker *checker);
t_bool	is_duplicate(char *argv[], int argc);

/*
** Get next line
*/
int		gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strdup(const char *s1);
void	gnl_nl_to_null(char *str);
int		gnl_free(void *line, char **remaining, int status);
char	*gnl_dup_free(char *to_free, char *to_dup);
char	*gnl_alloc_remaining(char *remaining);
int		get_next_line(int fd, char **line, char **remaining);
#endif
