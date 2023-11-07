SRC = change_dir.c char.c count.c dollar.c echo.c environment.c environment2.c environment3.c environment4.c environment5.c execute.c lexing.c lexer2.c lexer3.c parser.c parser2.c parser3.c parser4.c shell.c signals.c utils.c utils2.c utils3.c utils4.c utils5.c redirection.c redirection1.c redirection2.c redirection3.c redirection4.c errors.c
C = gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
RM = rm -rf

OBJS = $(SRC:.c=.o)

READLINE = readline

all: $(READLINE) $(LIBFT) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(CFLAGS) -L${PWD}/readline/lib -I${PWD}/readline/include/ -lreadline

$(LIBFT):
	make -C libft/ all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

fclean: clean
	$(RM) $(NAME)
	$(RM) readline-8.2 readline-8.2.tar.gz
	make -C libft/ fclean

clean:
	$(RM) $(OBJS)
	make -C libft/ clean

re: fclean all

.PHONY: all fclean clean re
