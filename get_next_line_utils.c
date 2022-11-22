/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:19:34 by jmouline          #+#    #+#             */
/*   Updated: 2022/11/22 20:51:31 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if ((char)c == 0)
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*ft_strjoin_normed(const char *s1, const char *s2, char *dest)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!dest)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	if (i < (len_s1 + len_s2))
	{
		while (i < len_s1)
		{
			dest[i] = s1[i];
			i++;
		}
		len_s1 = 0;
		while (s2[len_s1])
			dest[i++] = s2[len_s1++];
	}
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dest;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc(len_s1 + len_s2 + 1);
	while (len_s1 + len_s2 > 0)
		dest[len_s1-- + len_s2] = 0;
	if (!dest)
		return (NULL);
	dest = ft_strjoin_normed(s1, s2, dest);
	if (!dest)
		return (NULL);
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;

	d = (char *)dest;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*(char *)d = *(char *)src;
		d++;
		src++;
		n--;
	}
	return (dest);
}
