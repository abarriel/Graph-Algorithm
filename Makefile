# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/19 11:33:06 by abarriel          #+#    #+#              #
#    Updated: 2017/03/19 05:52:25 by abarriel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem-in

SRC		= lemin.c parser.c room.c tube.c algo.c print.c path.c tools.c send.c algo_.c

OBJ		= $(addprefix srcs/,$(SRC:.c=.o))

INCLUDES = ./includes/lemin.h

CFLAGS	=  -Wall -Wextra -Werror -I./includes/ -Ilibft/includes/

all: makefile libft $(NAME)

libft:
	@make -C libft

$(NAME): libft $(OBJ) $(INCLUDES)
	@gcc $(OBJ) -o $(NAME)  -Llibft -lft
	@echo "$^"

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ)
	@make fclean -C libft

re: fclean all

.PHONY: clean fclean re libft all
