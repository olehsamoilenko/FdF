NAME = name

all: $(NAME)

$(NAME):
	gcc main.c -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
