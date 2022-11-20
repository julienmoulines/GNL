NAME = get_next_line

CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=7 -o
AR = ar crs
RM = rm -f
NM = norminette
Lib_H = get_next_line.h \

SRCS = \
	get_next_line.c

SRCS_B = \
	get_next_line_utils.c

BONUS = \


all: $(NAME)

$(NAME): $(SRCS) $(SRCS_B)
	$(CC) $(CFLAGS) $@ $^

norme: $(SRCS) $(SRCS_B) $(BONUS) $(Lib_H)
	$(NM) $@ $^

bonus: $(BONUS)
	$(CC) $(NAME) $^

git: 
	git add .
	git commit -m "makefile"
	git push
	clear
	
clean:
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: norme all fclean re bonus clean