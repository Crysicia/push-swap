/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:14:05 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/13 14:27:24 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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

#endif