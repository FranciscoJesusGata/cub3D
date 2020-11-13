#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 12:43:45 by fgata-va          #+#    #+#              #
#    Updated: 2020/11/13 12:31:44 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS += -Wall -Werror -Wextra -I . -g

GNL = lib/GNL/get_next_line.c lib/GNL/get_next_line_utils.c

SRC = cub3d.c cub3d_utils.c cub3d_utils_2.c validate_args.c validate_map.c ft_save_map.c main.c

NAME = cub3d

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
	@rm -rf $(NAME) $(NAME).dSYM

re: clean all
