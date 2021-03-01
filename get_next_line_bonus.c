/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiguchi <thiguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:38:10 by thiguchi          #+#    #+#             */
/*   Updated: 2021/02/11 17:12:27 by thiguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1_len;
	size_t		s2_len;
	char		*join;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(join = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy(join + s1_len, s2, s2_len + 1);
	return (join);
}

static int		ft_find_newline(char **line, char **save)
{
	char		*old_line;
	char		*tmp;

	old_line = ft_strchr(*line, '\n');
	if (old_line == NULL)
	{
		*save = NULL;
		return (0);
	}
	else
	{
		tmp = ft_substr(*line, 0, old_line - *line);
		*save = ft_substr(old_line + 1, 0, ft_strlen(old_line) + 1);
		free(*line);
		*line = tmp;
		if (*line == NULL)
			return (-1);
		else if (*save == NULL)
		{
			free(*line);
			return (-1);
		}
		return (1);
	}
}

static int		ft_linejoin(int fd, char **line, char **save, char *buf)
{
	ssize_t		size;
	char		*tmp;

	if (!(*line = ft_strdup(*save)))
		return (-1);
	if (ft_strchr(*line, '\n') != NULL)
		return (1);
	while ((size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size] = '\0';
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
		if (*line == NULL)
			return (-1);
		if (ft_strchr(*line, '\n') != NULL)
			return (1);
	}
	if (*line[0] == '\0' && size == 0)
		return (0);
	else if (size == 0)
		return (1);
	else
		return (-1);
}

int				get_next_line(int fd, char **line)
{
	int			flag;
	char		*buf;
	static char	*save;

	if (fd < 0 || fd >= FOPEN_MAX || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!save)
	{
		if (!(save = ft_strdup("")))
		{
			free(buf);
			return (-1);
		}
	}
	flag = ft_linejoin(fd, line, &save, buf);
	free(buf);
	free(save);
	return (ft_find_newline(line, &save));
}
