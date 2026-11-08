/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadout <mahadout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 17:42:52 by mahadout          #+#    #+#             */
/*   Updated: 2026/11/08 16:43:55 by mahadout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sublen;
	size_t	strlen;
	char	*pmalloc;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		sublen = 0;
	else if (len > strlen - start)
		sublen = strlen - start;
	else
		sublen = len;
	pmalloc = malloc((sublen + 1) * sizeof(char));
	if (!pmalloc)
		return (NULL);
	i = 0;
	while (i < sublen)
	{
		pmalloc[i] = s[start + i];
		i++;
	}
	pmalloc[i] = '\0';
	return (pmalloc);
}

char	*grow_buffer(char *buffer, size_t len, size_t *cap)
{
	char	*new;
	size_t	i;

	*cap = 2 * len + BUFFER_SIZE + 1;
	new = malloc(*cap);
	if (!new)
		return (free(buffer), NULL);
	i = 0;
	while (i <= len)
	{
		new[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new);
}

size_t	l_count(char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	return (len);
}
