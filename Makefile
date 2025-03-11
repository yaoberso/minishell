# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nas <nas@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:35:28 by nadahman          #+#    #+#              #
#    Updated: 2025/03/10 20:33:57 by nas              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iparsing -Isignaux -Icommande -Ifree -Ipipe_redir -I$(READLINE_DIR)/include -g3

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

debug: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=readline.supp --log-file="leaks.log" ./minishell

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
