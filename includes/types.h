/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:14:05 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/27 09:41:23 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "../libft/libft.h"

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef struct		s_stacks
{
	t_list			*a;
	t_list			*b;
}					t_stacks;

typedef struct		s_push_swap
{
	t_stacks		stacks;
	t_list			*statements;
}					t_push_swap;

typedef struct		s_bounds
{
	int high;
	int low;
	int next_index;
	int starting_index;
	int size;
}					t_bounds;

#endif
