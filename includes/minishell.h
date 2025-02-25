/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:21:04 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/25 10:50:43 by nadahman         ###   ########.fr       */
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

// Structure pour les redirections
typedef struct s_redirection 
{
    char    *type;    // le type de redirection ça "<" ça ">" ou ça">>"
    char    *file;    // le fichier de redirection
    struct s_redirection *next;
} t_redirection;

// Structure pour les pipes
typedef struct s_pipe
{
    char *type;
    char *cmd_pipe;
    struct s_pipe *next;
} t_pipe;


// Structure pour les commandes
typedef struct s_cmd
{
	char *cmd;  // pour les commandes
	t_token *arg; // liste chainé qui va contenir les arguments
	t_redirection   *redirection; // liste chainé qui va contenir les redirections
    t_pipe  *pipe;
} t_cmd;




// Fonctions de parsing
void 	add_token(t_token **head, t_token *new);
t_token	*new_token(char *str);
void	parsing(char *str, t_cmd *cmd);
char 	*recup_token(char *str, int *index);
t_redirection    *found_redirection(char *str, int *index);
void    add_redirection(t_cmd *cmd, t_redirection *new_redir);
t_pipe  *found_pipe(char *str, int *index);
void    add_pipe(t_cmd *cmd, t_pipe *pipe);

// utils
void 	print_arguments(t_token *arg);
int    ft_isspace(char c);
#endif