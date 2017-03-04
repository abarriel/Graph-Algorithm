# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarriel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/19 11:33:06 by abarriel          #+#    #+#              #
#    Updated: 2017/02/19 11:33:07 by abarriel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem_in

SRC		= lemin.c parser.c room.c tube.c algo.c print.c djik.c

OBJ		= $(addprefix srcs/,$(SRC:.c=.o))

CFLAGS	=  -I./ -Ilibft/includes/

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(OBJ) -o $(NAME) -L libft/ -lft
	@echo "Lem-in..."

all: $(NAME)

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ)
	@make -C libft/ fclean

re: fclean $(NAME)
