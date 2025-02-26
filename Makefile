# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nas <nas@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:35:28 by nadahman          #+#    #+#              #
#    Updated: 2025/02/26 11:03:32 by nas              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iparsing -Isignaux -I$(READLINE_DIR)/include -g3
CC = gcc
OBJ = $(SRCS:.c=.o)

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    READLINE_DIR = $(shell brew --prefix readline)
else
    READLINE_DIR = /usr/include
endif

SRCS =	main.c \
		parsing/parsing.c \
		parsing/pars_utils.c \
		parsing/pars_utils2.c \
		signaux/signal.c
	 
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

