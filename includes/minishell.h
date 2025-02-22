/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:21:04 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/22 10:12:47 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"


// stucture en liste chainé qui va contenir tout les elements de la commande
typedef struct s_token
{
    char            *value;
    struct s_token  *next;
} t_token;

// Structure pour les commandes
typedef struct s_cmd
{
	char *cmd;  // pour les commandes
	t_token *arg; // liste chainé qui va contenir les arguments
} t_cmd;





void add_token(t_token **head, t_token *new);
t_token	*new_token(char *str);
void	parsing();
void	pars_one_arg(char *str, t_cmd *cmd);
void pars_mult(char *str, t_cmd *cmd);
char *recup_token(char *str, int *index);
void print_arguments(t_token *arg);

#endif