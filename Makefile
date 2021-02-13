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

NORMI = norminette

GNL = lib/GNL/get_next_line.c lib/GNL/get_next_line_utils.c

SRC = cub3d.c main.c cub3d_utils_1.c cub3d_utils_2.c cub3d_utils_3.c \
	cub3d_utils_4.c validate_args.c validate_args_2.c validate_map.c \
	ft_save_map.c graphics.c raycasting.c buffer_img.c bmp.c \
	sprites.c movement.c raycast_utils.c print_sprites.c free_data.c

BONUS = movement_bonus.c play_music_bonus.c

NAME = cub3D

LIBFT = -L lib/libftprintf -lftprintf

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
  MLX := -L . -lmlx -framework OpenGL -framework Appkit
  SRC += mac_functions.c
endif
ifeq ($(UNAME), Linux)
  MLX := -L lib/mlx_linux -lmlx -lXext -lX11
  SRC += linux_functions.c
  NORMI := ~/.norminette/norminette.rb
endif

all: git_submodules $(NAME)

bonus: git_submodules libft mlx
	$(CC) $(CFLAGS) -D BONUS $(SRC) $(BONUS) $(GNL) -lm $(LIBFT) $(MLX) -o $(NAME)

libft:
	@echo "							[        COMPILING LIBFT        ]"
	$(MAKE) -C lib/libftprintf all

ifeq ($(UNAME), Darwin)
mlx:
	@echo "							[    COMPILING MLX_BETA_2020    ]"
	$(MAKE) -C lib/mlx
	cp lib/mlx/libmlx.dylib .
endif
ifeq ($(UNAME), Linux)
mlx:
	@echo "							[      COMPILING LINUX_MLX      ]"
	@$(MAKE) -C lib/mlx_linux
endif

git_submodules:
	@echo "							[    DOWNLOADING DEPENDENCIES   ]"
	git submodule init
	git submodule update

$(NAME): libft mlx
	@echo "							[        COMPILING CUB3D        ]"
	$(CC) $(CFLAGS) $(SRC) $(GNL) -lm $(LIBFT) $(MLX) -o $(NAME)

norm:
	@echo "							************** CUB3D FILES **************"
	@$(NORMI) $(SRC) $(BONUS) cub3d_bonus.h cub3d.h keys.h
	@echo "							************* PRINTF FILES **************"
	@$(NORMI) lib/libftprintf/*.c lib/libftprintf/*.h
	@echo "							************** LIBFT FILES **************"
	@$(NORMI) lib/libftprintf/Libft/*.c lib/libftprintf/Libft/*.h
	@echo "							*************** GNL FILES ***************"
	@$(NORMI) lib/GNL/*.c lib/GNL/*.h

clean:
	@make -C lib/libftprintf fclean
	@make -C lib/mlx clean
	@make -C lib/mlx_linux clean
	@rm -rf libmlx.dylib*
	@rm -rf $(NAME) $(NAME).dSYM
	@rm -f screenshot.bmp

re: clean all
