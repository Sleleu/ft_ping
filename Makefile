# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 12:59:59 by sleleu            #+#    #+#              #
#    Updated: 2023/09/05 10:59:31 by sleleu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping

SRC_PATH = src
OBJ_PATH = obj

SOURCES = main.c

SRC = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJ = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
		$(CC) $(CFLAGS)  $(OBJ) -L libft -lft -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

libft/libft.a:
	make -C libft

clean:
		rm -rf $(OBJ_PATH)
		make clean -C libft

fclean: clean
		rm -rf $(NAME)
		make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
