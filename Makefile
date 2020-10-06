#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 12:43:45 by fgata-va          #+#    #+#              #
#    Updated: 2020/10/06 10:39:41 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS += -Wall -Werror -Wextra -I . -g

GNL = lib/GNL/get_next_line.c lib/GNL/get_next_line_utils.c

SRC = cube3d.c

NAME = cube3d

LIBFT = -L lib/libftprintf -lftprintf

MLX = -L . -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

libft:
	@$(MAKE) -C lib/libftprintf all

mlx:
	@$(MAKE) -C lib/mlx all
	mv lib/mlx/libmlx.dylib .

$(NAME): libft mlx
	$(CC) $(CFLAGS) $(SRC) $(GNL) $(LIBFT) $(MLX) -o $(NAME)

test: libft
	$(CC) $(CFLAGS) $(SRC) $(GNL) $(LIBFT)

clean:
	@make -C lib/libftprintf fclean
	@make -C lib/mlx clean
	@rm -rf libmlx.dylib
	@rm $(NAME)

re: fclean all
