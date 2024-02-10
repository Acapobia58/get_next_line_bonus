/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapobia <acapobia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:35:43 by acapobia          #+#    #+#             */
/*   Updated: 2023/11/27 18:35:43 by acapobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include "get_next_line.h"
//#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_salva_spazio(char *s, char *buf, int n)
{
	char	*temp;

	temp = s;
	s = ft_strjoin(temp, buf, (size_t)n);
	free(temp);
	if (!s)
	{
		s = NULL;
		return (s);
	}
	return (s);
}

char	*new_call(int fd, char *buf, char *s)
{
	int		byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		if (!s)
			s = ft_calloc(1, sizeof (char *));
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read <= 0)
		{
			if (ft_strlen(s) == 0)
			{
				free(s);
				s = NULL;
			}
			break ;
		}
		s = ft_salva_spazio(s, buf, byte_read);
		if (ft_strchr(s, '\n') || byte_read <= 0)
			break ;
	}
	return (s);
}

char	*check_call(char **line, char *s)
{
	char	*temp;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++ ;
	*line = ft_substr(s, 0, ++i);
	temp = ft_substr(s, 0, ft_strlen(s));
	free(s);
	if (temp)
		s = ft_substr(temp, i, ft_strlen(temp) - i);
	else
		s = NULL;
	if (!s)
	{
		free(s);
	}
	free(temp);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s[4095];
	char		*buf;

	if (fd < 0)
		return (NULL);
	line = NULL;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char *));
	if (!buf)
		return (NULL);
	s[fd] = new_call(fd, buf, s[fd]);
	free(buf);
	s[fd] = check_call(&line, s[fd]);
	if (!line || !(*line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
