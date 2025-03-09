# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yann <yann@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:35:28 by nadahman          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/03/09 12:18:40 by nas              ###   ########.fr        #
=======
#    Updated: 2025/03/06 10:49:10 by yann             ###   ########.fr        #
>>>>>>> commande-intern
#                                                                              #
# **************************************************************************** #

NAME = minishell
<<<<<<< HEAD
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iparsing -Isignaux -Ifree -I$(READLINE_DIR)/include -g3
=======
>>>>>>> commande-intern
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iparsing -Isignaux -I$(READLINE_DIR)/include -g3

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    READLINE_DIR = $(shell brew --prefix readline)
else
    READLINE_DIR = /usr/include
endif

SRCS = main.c \
	   utils.c \
       $(wildcard parsing/*.c) \
       $(wildcard signaux/*.c) \
       $(wildcard commande/*.c) \
	   $(wildcard free/*.c) \
	   $(wildcard pipe_redir/*.c) \
	   


OBJ = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_OBJ = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_OBJ) -L$(READLINE_DIR)/lib -lreadline -lncurses -o $(NAME)

$(LIBFT_OBJ):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
