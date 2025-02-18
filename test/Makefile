# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 19:47:10 by marvin            #+#    #+#              #
#    Updated: 2025/01/22 12:08:23 by nadahman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME_SERVER = server
NAME_CLIENT = client
CFLAGS     = -Wall -Wextra -Werror
CC         = gcc

# Fichiers sources
SRCS_SERVER = serveur.c printf/fonctions.c printf/fonctions2.c printf/ft_printf.c utils.c
SRCS_CLIENT = client.c printf/fonctions.c printf/fonctions2.c printf/ft_printf.c utils.c

# Fichiers objets
OBJ_SERVER = $(SRCS_SERVER:.c=.o)
OBJ_CLIENT = $(SRCS_CLIENT:.c=.o)

# Règle par défaut
all: $(NAME_SERVER) $(NAME_CLIENT)

# Compilation du serveur
$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

# Compilation du client
$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

# Nettoyage des objets
clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

# Nettoyage complet (objets + exécutables)
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

# Reconstruction complète
re: fclean all

# Règle pour créer les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règles supplémentaires
.PHONY: all clean fclean re
