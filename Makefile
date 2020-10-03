#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 12:43:45 by fgata-va          #+#    #+#              #
#    Updated: 2020/10/02 13:11:38 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS += -Wall -Werror -Wextra -I .

GNL = lib/GNL/get_next_line.c lib/GNL/get_next_line_utils.c

SRC = cube3d.c

NAME = cube3d

LIBFT = -L lib/libftprintf/ -lft

MLX = -L . -lmlx -framework OpenGL -framework Appkit

INCLUDE = -I lib/GNL/ -I lib/libftprintf/ -I lib/mlx/

libft:
	@$(MAKE) -C lib/libftprintf all

mlx:
	@$(MAKE) -C lib/mlx all
	mv lib/mlx/libmlx.dylib .

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) $(GNL) $(LIBFT) $(MLX) -o $(NAME)

clean:
	@make -C lib/libftprintf fclean
	@make -C lib/mlx clean
	@rm -rf libmlx.dylib
	@rm $(NAME)

re: fclean all
