# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 12:59:59 by sleleu            #+#    #+#              #
#    Updated: 2023/09/05 10:29:13 by sleleu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
		$(CC) $(CFLAGS)  $(SRC) -L libft -lft -o $(NAME)

libft/libft.a:
	make -C libft

clean:
		rm -rf $(OBJ)
		make clean -C libft

fclean: clean
		rm -rf $(NAME)
		make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
