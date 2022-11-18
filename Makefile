NAME = get_next_line

CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=1
RM = rm -f
NM = norminette
Lib_H = get_next_line.h \

SRCS = \
		get_next_line.c
	
BONUS = \

$(NAME): $(cc) $(SRCS)

norme: $(SRCS) $(BONUS) $(Lib_H)
	$(NM) $@ $^

all: $(NAME)
	
bonus: $(BONUS)
	$(CC) $(BONUS) $^

git: 
	git add .
	git commit -m "makefile"
	git push
	clear
	
clean:
	$(RM)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: norme all fclean re bonus clean