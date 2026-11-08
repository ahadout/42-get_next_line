/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadout <mahadout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 18:05:41 by mahadout          #+#    #+#             */
/*   Updated: 2026/11/08 17:27:17 by mahadout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# define FD_MAX 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*fill_buffer(int fd, char *buffer);
char	*extract_line(char *buffer);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*trim_buffer(char *buffer);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*grow_buffer(char *buffer, size_t len, size_t *cap);
size_t	l_count(char *buffer);

#endif