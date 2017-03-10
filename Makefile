# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/08 05:45:14 by lcharvol          #+#    #+#              #
#    Updated: 2017/03/08 05:45:15 by lcharvol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = snake

SRCS := srcs/main.c 
SRCS += srcs/ft_hooks.c
SRCS += srcs/ft_draw.c


FLAGS = -Wall -Werror -Wextra -I./includes

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L../includes/mlx/ -lmlx -framework OpenGL -framework AppKit ../libft/libft.a
	echo "Snake done"

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

