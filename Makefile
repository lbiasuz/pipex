# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 22:16:36 by lbiasuz           #+#    #+#              #
#    Updated: 2022/11/08 23:21:52 by lbiasuz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC						= gcc

OPTIONS				=	-Wall -Werror -Wextra -g3

NAME					=	pipex

SRC						= pipex.c pipex_utils.c

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

rep:
	rm -rf pipex
	make all

teste:
	$(CC) $(OPTIONS) teste.c $(DEPENDENCIES) -o teste

ret:
	rm -rf teste
	make teste