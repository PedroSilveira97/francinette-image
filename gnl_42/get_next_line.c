/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptavares <ptavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:26:18 by ptavares          #+#    #+#             */
/*   Updated: 2025/06/17 14:11:45 by ptavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*cleanup(char *buffer, char *leftover)
{
	free(buffer);
	free(leftover);
	return (NULL);
}

char	*read_file(int fd, char *leftover)
{
	char	*buffer;
	char	*aux;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(leftover, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			return (cleanup(buffer, leftover));
			leftover = NULL;
		}
		buffer[bytes] = '\0';
		aux = leftover;
		leftover = ft_strjoin(leftover, buffer);
		if (!leftover)
			return (cleanup(aux, buffer));
		free(aux);
	}
	free(buffer);
	return (leftover);
}

static char	*update_remainder(char *remainder)
{
	size_t	i;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
		return (NULL);
	return (ft_strdup(remainder + i + 1));
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;
	char		*new_leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = read_file(fd, leftover);
	if (!leftover)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = ft_get_line(leftover);
	if (!line || line[0] == '\0')
	{
		free(line);
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	new_leftover = update_remainder(leftover);
	free(leftover);
	leftover = new_leftover;
	return (line);
}
