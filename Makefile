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

SRC		=	main.c check.c attack.c

OBJ		= $(addprefix src/,$(SRC:.c=.o))

CFLAGS	=  -Wall -Wextra -Werror -Iincludes/ -Ilibft/includes/

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(OBJ) -o $(NAME) -L libft/ -lft -Ilibft/includes/
	@echo "Filler..."
all: $(NAME)

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ)
	@make -C libft/ fclean

re: fclean $(NAME)
