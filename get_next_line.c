/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptavares <ptavares@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:31:01 by ptavares          #+#    #+#             */
/*   Updated: 2025/06/27 12:21:01 by ptavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_all(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	rd;
	char	*tmp;

	buf = malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (!buf)
		return (NULL);
	rd = 1;
	while (!ft_strchr(stash, '\n') && rd > 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			ft_free_all(stash, buf);
		buf[rd] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (stash);
}

char	*extract_line(char **sth)
{
	char	*nw;
	char	*line;
	char	*aux;

	if (!*sth || **sth == '\0')
		return (NULL);
	nw = ft_strchr(*sth, '\n');
	aux = ft_substr(*sth, nw - *sth + 1, ft_strlen(*sth) - (nw - *sth + 1));
	if (nw)
	{
		line = ft_substr(*sth, 0, nw - *sth + 1);
		free(*sth);
		*sth = aux;
		if (*sth && **sth == '\0')
		{
			free(*sth);
			return (NULL);
		}
	}
	else
	{
		line = *sth;
		*sth = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(&stash);
	return (line);
}
