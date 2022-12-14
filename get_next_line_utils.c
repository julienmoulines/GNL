#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	int		len;
	char	*dest;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	dest = malloc(len + 1);
	if (!(dest))
		return (free((void*)s), NULL);
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static char	*ft_strjoin_normed(char *s1, char *s2, char *dest)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!dest)
		return (free(s1), NULL);
	if (!s1)
		return (free(s1), ft_strdup(s2));
	if (!s2)
		return (free(s1), NULL);
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
	free(s1);
	free(s2);
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dest;
	size_t	i;

	i = 0;
	if (!s1)
		return (free(s1), ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc(len_s1 + len_s2 + 1);
	if (!dest)
		return (free(s1), free(s2), NULL);
	while (i < len_s1 + len_s2 + 1)
		dest[i++] = '\0';
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