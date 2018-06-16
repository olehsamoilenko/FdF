NAME = fdf

HEADER = fdf.h

FLAGS = -Wall -Werror -Wextra

SRC =	main.c

OBJ = $(SRC:.c=.o)

%.o: %.c $(HEADER)
	gcc -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc $(SRC) -o $(NAME) -I /usr/local/include -L /usr/local/lib libft/libft.a -lmlx -framework OpenGL -framework AppKit

clean:
	make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	@rm -f $(NAME)

re: fclean all