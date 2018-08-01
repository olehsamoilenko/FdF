# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osamoile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 11:59:56 by osamoile          #+#    #+#              #
#    Updated: 2018/03/26 12:08:46 by osamoile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADERS = -I ./includes
FLAGS = -Wall -Werror -Wextra

LIST =	ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memccpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strdup \
		ft_strcpy \
		ft_strncpy \
		ft_strcat \
		ft_strncat \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strstr\
		ft_strnstr \
		ft_strcmp \
		ft_strncmp \
		ft_atoi \
		ft_atoi_base \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_memalloc \
		ft_memdel \
		ft_strnew \
		ft_strdel \
		ft_strclr \
		ft_striter \
		ft_striteri \
		ft_strmap \
		ft_strmapi \
		ft_strequ \
		ft_strnequ \
		ft_strsub \
		ft_strjoin \
		ft_strtrim \
		ft_strsplit \
		ft_itoa \
		ft_itoa_base \
		ft_putchar \
		ft_putstr \
		ft_putendl \
		ft_putnbr \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_lstnew \
		ft_lstdelone \
		ft_lstdel \
		ft_lstadd \
		ft_lstiter \
		ft_lstmap \
		ft_iswhitespace \
		ft_countdigits \
		ft_wordscount \
		ft_arrclr \
		ft_lstaddend \
		get_next_line \
		ft_printf \
		parsing \
		recognise \
		type_c \
		type_hex \
		type_integer \
		type_o \
		type_s \
		type_unsigned

OBJ = $(addprefix obj/, $(addsuffix .o, $(LIST)))

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)

obj/%.o: src/%.c
	@gcc $(FLAGS) -c $< -o $@ $(HEADERS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
