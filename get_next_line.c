/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:51:30 by jmouline          #+#    #+#             */
/*   Updated: 2022/12/14 05:12:02 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *s)
{
	char	*dest;
	int		pos;
	int		i;

	if (*s == 0)
		return (free(s), NULL);
	pos = ft_strchr(s, '\n');
	if (pos < 0)
		dest = malloc(ft_strlen(s) + 1);
	else
		dest = malloc(pos + 2);
	if (!dest)
		return (NULL);
	i = 0;
	dest[pos + 1] = '\0';
	while (s[i] != '\n' && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		dest[i] = '\n';
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len && start < ft_strlen(s))
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_new_stock(char *stock)
{
	char	*dest;
	int		pos;

	pos = ft_strchr(stock, '\n');
	if (pos < 1 && ft_strlen(stock) < 1)
		return (NULL);
	pos++;
	dest = ft_substr(stock, pos, ft_strlen(stock));
	if (dest[0] == '\0' )
		dest[0] = '\0';
	free (stock);
	return (dest);
}

int	ft_get_buffer(int fd, char **stock, int count_read)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	while (ft_strchr(*stock, '\n') < 0 && count_read != 0)
	{
		count_read = read(fd, buffer, BUFFER_SIZE);
		if (count_read == -1)
			return (free(buffer), 0);
		buffer[count_read] = '\0';
		*stock = ft_strjoin(*stock, buffer);
	}
	free(buffer);
	return (count_read);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;
	int			count_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	count_read = 1;
	if (!stock)
	{
		stock = malloc(1);
		stock[0] = '\0';
	}
	count_read = ft_get_buffer(fd, &stock, count_read);
	line = ft_line(stock);
	if (!line)
		return (NULL);
	if (count_read == 0)
	{
		free(stock);
		stock = NULL;
	}
	else
		stock = ft_new_stock(stock);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *test;
	test = get_next_line(fd);
	while (test)
	{
		printf(": %s", test);
		free(test);
		test = get_next_line(fd);
	}
	close(fd);
}