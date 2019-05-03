# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osamoile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/01 15:53:40 by osamoile          #+#    #+#              #
#    Updated: 2018/08/08 22:22:39 by osamoile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			fdf
INC =			-I ./includes \
				-I ./libft/includes \
				-I ./minilibx
FLAGS =			#-Wall -Werror -Wextra
MAKEFLAGS +=	--no-print-directory
LIBS =			-L ./libft -lft \
				-L ./minilibx -lmlx

ifeq ($(shell uname), Linux)
	LIBS += -lX11 -lXext -lm
endif
ifeq ($(shell uname), Darwin)
	LIBS += -framework OpenGL -framework AppKit
endif

LIST =			main \
				line \
				key_hook \
				draw \
				transformation \
				init \
				parse \
				intro

SRC = $(addprefix src/, $(addsuffix .c, $(LIST)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(LIST)))

obj/%.o: src/%.c
	@gcc $(FLAGS) -c $< -o $@ $(INC)

all: $(NAME)


$(NAME): $(OBJ)
	@make -C libft
	@gcc $(OBJ) -o $(NAME) $(LIBS) $(INC)

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

