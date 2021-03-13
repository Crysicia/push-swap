/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:03:56 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/13 15:35:49 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

void init_checker(t_stacks *stacks);
t_bool parse_arguments(t_stacks *stacks, char *arg);
void ft_error(t_stacks *stacks);

/*
** Utils
*/
t_bool ft_malloc(void **pointer, size_t size);

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
