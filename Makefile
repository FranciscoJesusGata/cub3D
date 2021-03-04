#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 12:43:45 by fgata-va          #+#    #+#              #
#    Updated: 2021/02/24 12:26:48 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS += -Wall -Werror -Wextra -I . -g

NORMI = old_norminette

GNL = lib/GNL/get_next_line.c lib/GNL/get_next_line_utils.c

SRC = cub3d.c main.c cub3d_utils_1.c cub3d_utils_2.c cub3d_utils_3.c \
	cub3d_utils_4.c validate_args.c validate_args_2.c validate_map.c \
	ft_save_map.c graphics.c raycasting.c buffer_img.c bmp.c \
	sprites.c movement.c raycast_utils.c print_sprites.c free_data.c

BONUS = movement_bonus.c play_music_bonus.c

OBJS = $(SRC:.c=.o)

BONUSOBJS = $(BONUS:.c=.o)

NAME = cub3D

BONUS_NAME = cub3D_bonus

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

all: git_submodules libft mlx $(NAME)

bonus: git_submodules libft mlx $(BONUS_NAME)

$(BONUS_NAME):
	@echo "							[        COMPILING BONUS        ]"
	$(CC) $(CFLAGS) -c -D BONUS=1 $(SRC) $(BONUS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS) $(BONUSOBJS) $(GNL) -lm $(LIBFT) $(MLX)

$(NAME):
	@echo "							[        COMPILING CUB3D        ]"
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) -lm $(LIBFT) $(MLX) -o $(NAME)

libft:
	@echo "							[        COMPILING LIBFT        ]"
	$(MAKE) -C lib/libftprintf all

git_submodules:
	@echo "							[    DOWNLOADING DEPENDENCIES   ]"
	git submodule init
	git submodule update

ifeq ($(UNAME), Darwin)
mlx:
	@echo "							[    COMPILING MLX_BETA_2020    ]"
	$(MAKE) -C lib/mlx
	@cp lib/mlx/libmlx.dylib .
endif
ifeq ($(UNAME), Linux)
mlx:
	@echo "							[      COMPILING LINUX_MLX      ]"
	@$(MAKE) -C lib/mlx_linux
endif

clean:
	@make -C lib/libftprintf clean
	@make -C lib/mlx clean
	@rm -rf $(OBJS)
	@rm -rf $(BONUSOBJS)

fclean: clean
	@make -C lib/libftprintf fclean
	@make -C lib/mlx_linux clean
	@rm -rf libmlx.dylib*
	@rm -rf $(NAME) $(NAME).dSYM
	@rm -rf $(BONUS_NAME) $(BONUS_NAME).dSYM
	@rm -f screenshot.bmp

norm:
	@echo "							************** CUB3D FILES **************"
	@$(NORMI) $(SRC) cub3d.h keys.h
	@echo "							************* PRINTF FILES **************"
	@$(NORMI) lib/libftprintf/
	@echo "							************** LIBFT FILES **************"
	@$(NORMI) lib/libftprintf/Libft/
	@echo "							*************** GNL FILES ***************"
	@$(NORMI) lib/GNL/

re: fclean all
