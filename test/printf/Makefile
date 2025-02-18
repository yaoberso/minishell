# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/15 11:01:56 by nadahman          #+#    #+#              #
#    Updated: 2024/10/16 13:42:41 by nadahman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
OBJ 	= $(SRCS:.c=.o)

#FICHIERS SOURCES
SRCS	= 	ft_printf.c \
			fonctions.c \
			fonctions2.c

#REGLES
all: $(NAME)

#COMPILATION DE LA BIBLIOTHEQUE
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

#COMPILATION DES FICHIERS .c EN .o
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

#NETTOYAGE DES FICHIERS OBJETS
clean:
	rm -f $(OBJ)

#NETTOYAGE COMPLET
fclean: clean
	rm -f $(NAME)

#RECONSTRUCTION COMPLETE
re: fclean all

.PHONY: all clean fclean re

