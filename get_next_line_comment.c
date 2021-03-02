/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiguchi <thiguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:39:28 by thiguchi          #+#    #+#             */
/*   Updated: 2021/02/28 12:50:26 by thiguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	old_line = ft_strchr(*line, '\n');//改行されたところから
	if (old_line == NULL)//最後は改行がない
	{
		*save = NULL;
		return (0);
	}
	else
	{
		tmp = ft_substr(*line, 0, old_line - *line);//改行前の文字列
		*save = ft_substr(old_line + 1, 0, ft_strlen(old_line) + 1);//改行後の文字列
		free(*line);//全部tmpとsaveにうつしたのでもういらない
		*line = tmp;//出力されるline
		if (*line == NULL)
			return (-1);
		else if (*save == NULL)//コピーがうまくできなかったら
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

	if (!(*line = ft_strdup(*save)))//save(改行後の文字列)をlineに移行
		return (-1);
	if (ft_strchr(*line, '\n') != NULL)//もしlineの中に改行があるならそのままfind_newlineへ、一回の読み込みで改行が２回あったら？
		return (1);
	while ((size = read(fd, buf, BUFFER_SIZE)) > 0)//読み込めるなら、bufに格納される
	{
		buf[size] = '\0';
		tmp = ft_strjoin(*line, buf);//改行後＋次のbuffersize分の文字列を繋げる
		free(*line);
		*line = tmp;//改行後＋次のbuffersize分の文字列を繋げた物
		//if (*line == NULL)  になることない
		//	return (-1);
		if (ft_strchr(*line, '\n') != NULL)//改行があったらfind_newlineに進む
			return (1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*save;

	if (fd < 0 || fd >= FOPEN_MAX || line == NULL || BUFFER_SIZE <= 0) //ファイル読み込みのエラー処理
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))//一回分の読み込みメモリを確保
		return (-1);
	if (!save)//初回
	{
		if (!(save = ft_strdup("")))
		{
			free(buf);
			return (-1);
		}
	}
	ft_linejoin(fd, line, &save, buf);//改行後とbuffersize分の文字列の連結
	free(buf);
	free(save);
	return (ft_find_newline(line, &save));//出力するlineの生成とsaveの保存
}
