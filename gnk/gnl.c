#include "gnl.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-2);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
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

char	*ft_line(char *s)
{
	char	*dest;
	int		pos;
	int		i;
	int		j;

	pos = ft_strchr(s, '\n');
	dest = malloc(pos + 2);
	if (!dest)
		return (NULL);
	i = 0;
	pos++;
	dest[pos] = 0;
	while (s[i - 1] != '\n' && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_new_stock(char *stock)
{
	char	*dest;
	int		pos;
	int		i;

	i = 0;
	pos = ft_strchr(stock, '\n');
	dest = calloc(ft_strlen(stock) - pos + 1, 1);
	pos++;
	while (stock[pos])
		dest[i++] = stock[pos++];
	if (dest[0] == '\n' || dest[0] == 0)
		dest[0] = 0;
	return (dest);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char *stock;
	int			count_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = calloc(BUFFER_SIZE + 1, 1);
	if (!stock)
	{
		count_read = 1;
		stock = calloc(1, 1);
		if (!stock)
			return (NULL);
	}
	if (!buffer || !stock)
		return (NULL);
	while (ft_strchr(stock, '\n') < 0 && count_read != 0)
	{
		count_read = read(fd, buffer, BUFFER_SIZE);
		if (count_read == -1)
			return (free(buffer), NULL);
		if (count_read == 0 || (count_read == 1 && BUFFER_SIZE != 1))
			break ;
		stock = ft_strjoin(stock, buffer);
		if (!stock)
		{
			//free(stock);
			break ;
		}
	}
	line = ft_line(stock);
	stock = ft_new_stock(stock);
	if (!line || !stock)
		return (NULL);
	free(buffer);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd;
	int i = 1;
	fd = open("test.txt", O_RDONLY);
	write(fd, "test\ntest2\n", 14);
	char *test;
	while (i < 9)
	{
		test = get_next_line(fd);
		if (!test)
			return (printf("\nRien a afficher !\n"));
		printf(": %s\n", test);
		free(test);
		i++;
	}
}