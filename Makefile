NAME = fdf

HEADER = -I ./includes -I ./libft/includes 

FLAGS = -Wall -Werror -Wextra
LIBFLAGS = libft/libft.a -lmlx -framework OpenGL -framework AppKit

LIST =	main \
		line \
		key_hook \
		print_lines

SRC = $(addprefix src/, $(addsuffix .c, $(LIST)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(LIST)))

obj/%.o: src/%.c
	#FLAGS
	@gcc -c $< -o $@ $(HEADER)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	#FLAGS
	@gcc $(SRC) -o $(NAME) $(HEADER) $(LIBFLAGS)

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all