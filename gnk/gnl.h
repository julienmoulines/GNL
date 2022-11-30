#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);

int		ft_strchrr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif