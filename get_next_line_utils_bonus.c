/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jul.moulines@free.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:58:09 by jmouline          #+#    #+#             */
/*   Updated: 2022/12/18 14:55:14 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin_normed(char *s1, char *s2, char *dest)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!dest)
		return (NULL);
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
		len_s1 = '\0';
		while (s2[len_s1])
			dest[i++] = s2[len_s1++];
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dest;
	size_t	i;

	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc(len_s1 + len_s2 + 1);
	if (!dest)
		return (NULL);
	while (i < len_s1 + len_s2 + 1)
		dest[i++] = '\0';
	dest = ft_strjoin_normed(s1, s2, dest);
	if (!dest)
		return (NULL);
	free(s1);
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

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
