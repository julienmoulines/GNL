/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jul.moulines@free.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:51:30 by jmouline          #+#    #+#             */
/*   Updated: 2022/12/03 20:38:03 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *s)
{
	char	*dest;
	int		pos;
	int		i;

	pos = ft_strchr(s, '\n');
	if (pos < 0)
	{
		dest = malloc(ft_strlen(s) + 1);
		pos = ft_strlen(s);
	}
	else
		dest = malloc(pos + 2);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
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
	dest = ft_substr(stock, pos, ft_strlen(stock) - (pos - 1));
	if (stock[0] == '\0')
		dest[0] = '\0';
	free (stock);
	return (dest);
}

int	ft_get_buffer(int fd, char **stock, int count_read)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer || !stock)
		return (0);
	while (ft_strchr(*stock, '\n') < 0 && count_read != 0)
	{
		count_read = read(fd, buffer, BUFFER_SIZE);
		if (count_read == -1)
			return (free(buffer), 0);
		buffer[count_read] = '\0';
		*stock = ft_strjoin(*stock, buffer);
		if (!stock)
		{
			free(*stock);
			break ;
		}
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
		if (!stock)
			return (NULL);
	}
	count_read = ft_get_buffer(fd, &stock, count_read);
	line = ft_line(stock);
	if (count_read == 0 && !stock)
		return(free(stock), NULL);
	else
		stock = ft_new_stock(stock);
	if (!line)
		return (NULL);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd;
	int i = 1;
	fd = open("test.txt", O_RDONLY);
	while (i < 10)
	{
		printf(": %s", get_next_line(fd));
		i++;
	}
}