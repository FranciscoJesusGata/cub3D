# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/22 01:39:28 by fgata-va          #+#    #+#              #
#    Updated: 2020/01/14 20:18:38 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I . -g -D BUFFER_SIZE=100000

SRC = get_next_line.c get_next_line_utils.c main.c

NAME = gnl

all: $(NAME)

$(NAME):
		@$(CC) $(CFLAGS) $(SRC)

fclean:
		@rm -f *.out

re: fclean all

.PHONY: all fclean re
