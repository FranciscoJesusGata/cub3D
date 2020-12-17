#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 12:43:45 by fgata-va          #+#    #+#              #
#    Updated: 2020/11/30 10:44:17 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS += -Wall -Werror -Wextra -I . -g

GNL = lib/GNL/get_next_line.c lib/GNL/get_next_line_utils.c

SRC = cub3d.c  main.c cub3d_utils_1.c cub3d_utils_2.c cub3d_utils_3.c \
	cub3d_utils_4.c validate_args.c validate_args_2.c validate_map.c \
	ft_save_map.c graphics.c ft_raycasting.c buffer_graphics.c

NAME = cub3D

LIBFT = -L lib/libftprintf -lftprintf

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
  MLX := -L . -lmlx -framework OpenGL -framework Appkit
endif
ifeq ($(UNAME), Linux)
  MLX := -L lib/mlx_linux -lmlx -lXext -lX11
endif

all: $(NAME)

libft:
	@$(MAKE) -C lib/libftprintf all

ifeq ($(UNAME), Darwin)
mlx:
	@$(MAKE) -C lib/mlx
	cp lib/mlx/libmlx.dylib .
endif
ifeq ($(UNAME), Linux)
mlx:
	@$(MAKE) -C lib/mlx_linux
endif

git_submodules:
	git submodule init
	git submodule foreach git pull origin master

$(NAME): libft mlx
	$(CC) $(CFLAGS) $(SRC) $(GNL) -lm $(LIBFT) $(MLX) -o $(NAME)

test: libft
	$(CC) $(CFLAGS) $(SRC) $(GNL) $(LIBFT)

norm:
	norminette $(SRC) cub3d.h keys.h

clean:
	@make -C lib/libftprintf fclean
	@make -C lib/mlx clean
	@make -C lib/mlx_linux clean
	@rm -rf libmlx.dylib*
	@rm -rf $(NAME) $(NAME).dSYM

re: clean all
