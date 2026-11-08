/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadout <mahadout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 18:05:44 by mahadout          #+#    #+#             */
/*   Updated: 2026/11/07 18:59:14 by mahadout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_buffer(int fd, char *buffer)
{
	size_t	len;
	size_t	cap;
	ssize_t	n;

	if (buffer[l_count(buffer)] == '\n')
		return (buffer);
	len = ft_strlen(buffer);
	cap = len + 1;
	n = 1;
	while (n > 0)
	{
		if (len + BUFFER_SIZE + 1 > cap)
			buffer = grow_buffer(buffer, len, &cap);
		if (!buffer)
			return (NULL);
		n = read(fd, buffer + len, BUFFER_SIZE);
		if (n < 0)
			return (free(buffer), NULL);
		buffer[len + n] = '\0';
		if (buffer[len + l_count(buffer + len)] == '\n')
			break ;
		len += n;
	}
	return (buffer);
}

char	*extract_line(char *buffer)
{
	size_t	len;

	len = l_count(buffer);
	if (buffer[len] == '\n')
		len++;
	return (ft_substr(buffer, 0, len));
}

size_t	guard(char *str, size_t start, size_t len)
{
	size_t	count;
	size_t	strlen;

	strlen = ft_strlen(str);
	if (start >= strlen)
		count = 0;
	else if (len > strlen - start)
		count = strlen - start;
	else
		count = len;
	return (count);
}

char	*trim_buffer(char *buffer)
{
	size_t	start;
	char	*rest;

	start = l_count(buffer);
	if (buffer[start] == '\n')
		start++;
	rest = ft_substr(buffer, start, ft_strlen(buffer));
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_substr("", 0, 0);
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = fill_buffer(fd, buffer[fd]);
	if (!buffer[fd] || !*buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = extract_line(buffer[fd]);
	if (!line)
		return (NULL);
	buffer[fd] = trim_buffer(buffer[fd]);
	return (line);
}
