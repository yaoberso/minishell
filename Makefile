# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yann <yann@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:35:28 by nadahman          #+#    #+#              #
#    Updated: 2025/02/21 11:06:57 by yann             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3
READLINE_DIR = $(shell brew --prefix readline)
INCLUDES = -I$(READLINE_DIR)/include
LIBS = -L$(READLINE_DIR)/lib

CC = gcc
SRCS = main.c
OBJ = $(SRCS:.c=.o)
LIBFT_OBJ = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_OBJ) $(INCLUDES) $(LIBS) -lreadline -lncurses -o $(NAME)

$(LIBFT_OBJ):
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re