# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 10:21:02 by marvin            #+#    #+#              #
#    Updated: 2024/10/06 10:21:02 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFLAGS	= -Wall -Wextra -Werror
CC		= gcc
OBJS 	= $(SRCS:.c=.o)

#FICHIERS SOURCES
SRCS	= ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_striteri.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c 

#REGLES
all: $(NAME)

#COMPILATION DE LA BIBLIOTHEQUE
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

#COMPILATION DES FICHIERS .c EN .o
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

#NETTOYAGE DES FICHIERS OBJETS
clean:
	rm -f $(OBJS)

#NETTOYAGE COMPLET
fclean: clean
	rm -f $(NAME)

#RECONSTRUCTION COMPLETE
re: fclean all

.PHONY: all clean fclean re

