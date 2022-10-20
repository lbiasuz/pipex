# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 22:16:36 by lbiasuz           #+#    #+#              #
#    Updated: 2022/10/09 11:21:10 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC						= gcc

OPTIONS				=	-Wall -Werror -Wextra -g3

NAME					=	pipex

SRC						= pipex.c

DEPENDENCIES	=	libft.a

$(NAME): $(DEPENDENCIES)
	$(CC) $(OPTIONS) $(SRC) $(DEPENDENCIES) -o $(NAME)

$(DEPENDENCIES):
	make -C libft/
	mv libft/libft.a libft.a

all: $(NAME)

clean:
	make -C libft/ clean
	rm -f $(DEPENDENCIES)

fclean: clean
	rm -f $(NAME)

re: fclean all
