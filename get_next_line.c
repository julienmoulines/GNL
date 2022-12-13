#include "get_next_line.h"

int	ft_read(int fd, char **stock, int count_read)
{
	char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (!ft_strchr(*stock, '\n') && count_read)
	{
		count_read = read(fd, buff, BUFFER_SIZE);
		if (count_read == -1)
			return (free(buff), 0);
		buff[count_read] = '\0';
		*stock = ft_strjoin(*stock, buff);
	}
	free(buff);
	return (count_read);
}

char	*ft_get_line(char *stock)
{
	int	i;
	int	j;
	char	*dest;

	j = 0;
	i = 0;
	if (!stock || !stock[i])
		return (NULL);
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock[i] == '\n')
		i++;
	dest = malloc(i + 1);
	i = 0;
	while (stock[j] != '\n' && stock[j])
		dest[i++] = stock[j++];
	dest[i] = stock[j];
	if (dest[i] != '\0')
		dest[++i] = '\0';
	stock = NULL;
	free(stock);
	return (dest);
}

char	*ft_new_stock(char *stock, int count_read)
{
	char	*dest;
	int	i;
	int	j;

	j = 0;
	if (count_read == 0)
		return (free(stock), NULL);
	while (*stock != '\n' && *stock)
		stock++;
	if (*stock == '\0')
		return (free(stock), NULL);
	stock++;
	while (stock[j])
		j++;
	dest = malloc(j + 1);
	dest[j] = '\0';
	j = 0;
	i = 0;
	while (stock[j])
		dest[j++] = stock[i++];
	stock = NULL;
	free(stock);
	return (dest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;
	int			count_read;

	count_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	count_read = ft_read(fd, &stock, count_read);
	line = ft_get_line(stock);
	//if (count_read == 0)
		//free(stock);
	stock = ft_new_stock(stock, count_read);
	if (!line)
		return (NULL);
	return (line);
}


#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	char *test;
	int i = 0;
	test = get_next_line(fd);
	while (test)
	{
		printf(": %s", test);
		free(test);
		test = get_next_line(fd);
		i++;
	}
	free(test);
	close(fd);
}