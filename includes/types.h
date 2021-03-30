/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:14:05 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/30 14:38:14 by lpassera         ###   ########.fr       */
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
	int				high;
	int				low;
	int				next_index;
	int				starting_index;
	int				size;
}					t_bounds;

typedef struct		s_args
{
	t_bool			color;
	t_bool			verbose;
	int				index;
}					t_args;

typedef struct		s_display
{
	int				biggest_stack;
	int				stack_a_size;
	int				stack_b_size;
	t_list			*stack_a;
	t_list 			*stack_b;
}					t_display;

#endif
