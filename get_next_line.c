/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiguchi <thiguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */  
/*   Created: 2021/02/28 11:39:28 by thiguchi          #+#    #+#             */
/*   Updated: 2021/03/02 11:32:53 by thiguchi         ###   ########.fr       */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_allfree(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

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
	if (read(fd, buf, BUFFER_SIZE) < 0)
		return (-1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*save;
	int			flag;

	flag = 0;
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
	if ((flag = ft_linejoin(fd, line, &save, buf)) < 0)
	{
		ft_allfree(buf, save);
		return (-1);
	}
	ft_allfree(buf, save);
	return (ft_find_newline(line, &save));
}
