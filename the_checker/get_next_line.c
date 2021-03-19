/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:31:00 by lpassera          #+#    #+#             */
/*   Updated: 2021/03/19 16:45:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	gnl_nl_to_null(char *str)
{
	size_t index;

	if (!str)
		return ;
	index = 0;
	while (str[index])
	{
		if (str[index] == '\n')
		{
			str[index] = '\0';
			return ;
		}
		index++;
	}
}

int		gnl_free(void *line, char **remaining, int status)
{
	if (status == -1)
		free(line);
	free(*remaining);
	*remaining = NULL;
	return (status);
}

char	*gnl_dup_free(char *to_free, char *to_dup)
{
	char *dup;

	dup = gnl_strdup(to_dup);
	free(to_free);
	return (dup);
}

char	*gnl_alloc_remaining(char *remaining)
{
	if (remaining)
		return (remaining);
	return (gnl_strdup(""));
}

int		get_next_line(int fd, char **line, char **remaining)
{
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || !line || read(fd, buffer, 0) || BUFFER_SIZE <= 0
			|| !(*remaining = gnl_alloc_remaining(*remaining)))
		return (-1);
	while (!gnl_strchr(*remaining, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		*remaining = gnl_strjoin(*remaining, buffer);
	}
	gnl_nl_to_null(*remaining);
	*line = gnl_strdup(*remaining);
	if (bytes_read == 0)
		return (gnl_free(*line, remaining, 0));
	*remaining = gnl_dup_free(*remaining,
					&(*remaining)[ft_strlen(*remaining) + 1]);
	if (!*line || !*remaining || bytes_read == -1)
		return (gnl_free(*line, remaining, -1));
	return (1);
}
