# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 12:43:45 by fgata-va          #+#    #+#              #
#    Updated: 2020/09/29 13:41:02 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS += -Wall -Werror -Wextra -I .

GNL = lib/GNL/get_next_line.c lib/GNL/get_next_line_utils.c

SRC = cube3d.c

NAME = cube3d

LIBFT = -L lib/libftprintf/ -lft

MLX = -L lib/mlx/ -lmlx -framework OpenGL -framework Appkit

INCLUDE = -I lib/GNL/ -I lib/libftprintf/ -I lib/mlx/

lib:
	@$(MAKE) -C lib/libftprintf all

mlx:
	@$(MAKE) -C lib/mlx all

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) $(GNL) $(LIBFT) $(MLX) -o $(NAME)

clean:
	@rm $(NAME)
	@make -C lib/libftprintf fclean
	@make -C lib/mlx fclean

re: fclean all
