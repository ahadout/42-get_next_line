/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadout <mahadout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:17:35 by mahadout          #+#    #+#             */
/*   Updated: 2026/11/08 16:44:01 by mahadout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_substr("", 0, 0);
	if (!buffer)
		return (NULL);
	buffer = fill_buffer(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(buffer);
	if (!line)
		return (NULL);
	buffer = trim_buffer(buffer);
	return (line);
}
