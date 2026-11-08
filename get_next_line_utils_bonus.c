/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadout <mahadout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 18:05:46 by mahadout          #+#    #+#             */
/*   Updated: 2026/11/07 18:57:55 by mahadout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_substr(char *str, size_t start, size_t len)
{
	size_t	count;
	char	*sub;
	size_t	i;

	if (!str)
		return (NULL);
	count = guard(str, start, len);
	sub = malloc(count + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
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
