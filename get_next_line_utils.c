/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiguchi <thiguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:40:02 by thiguchi          #+#    #+#             */
/*   Updated: 2021/02/11 16:59:13 by thiguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0 && *s == '\0')
		return ((char *)s);
	return (NULL);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i] != '\0')
		i++;
	if (!len)
		return (i);
	while (0 < (len - 1) && *src != '\0')
	{
		*dst++ = *src++;
		len--;
	}
	*dst = '\0';
	return (i);
}

char		*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	if (!(dup = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (0);
	if (len <= 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
