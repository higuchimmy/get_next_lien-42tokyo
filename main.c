/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiguchi <thiguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:40:06 by thiguchi          #+#    #+#             */
/*   Updated: 2021/02/11 17:14:25 by thiguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

#define END_READ -1

int main(int argc, char *argv[])
{
	char	*line;
	int fd_count = argc - 1;
	int fd[fd_count];
	int ret[fd_count];
	int num[fd_count];
	int i = 0;
	int j = 0;

	if (fd_count <= 0)
		return (0);
	while (i < fd_count)
	{
		fd[i] = open(argv[i + 1], O_RDONLY);
		num[i] = 0;
		i++;
	}
	i = 0;
	while (1)
	{
		if (fd[i] != END_READ)
		{
			ret[i] = get_next_line(fd[i], &line);
			num[i]++;
			printf("file :%d, ret :%d, num :%d, line :%s\n", i, ret[i], num[i], line);
			free(line);
			if (ret[i] <= 0)
				fd[i++] = END_READ;
		}
		for (j = 0; j < fd_count; j++)
			if (fd[j] != END_READ)
				break;
		if (j == fd_count)
			break;
		i++;
		if (i >= fd_count)
			i = 0; 
	}
	//system("leaks a.out");
	return (0);
}
