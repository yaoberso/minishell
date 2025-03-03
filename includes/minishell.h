/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:21:04 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/03 11:39:41 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>

// stucture en liste chainé qui va contenir tout les elements de la commande
typedef struct s_token
{
	char					*value;
	struct s_token			*next;
}							t_token;

// Structure pour les redirections
typedef struct s_redirection
{
	char *type; // le type de redirection ça "<" ça ">" ou ça">>"
	char *file; // le fichier de redirection
	struct s_redirection	*next;
}							t_redirection;

// Structure pour les commandes
typedef struct s_cmd
{
	char *cmd;                  // pour les commandes
	t_token *arg;               // liste chainé qui va contenir les arguments
	t_redirection *redirection; // liste chainé qui va contenir les redirections
	struct s_cmd *next_cmd;     // structure cree des qu un pipe est trouve
	struct s_cmd			*prev_cmd;
}							t_cmd;

// Fonctions de parsing
void						add_token(t_token **head, t_token *new);
t_token						*new_token(char *str);
void						parsing(char *str, t_cmd *cmd);
char						*recup_token(char *str, int *index);
t_redirection				*found_redirection(char *str, int *index);
void						add_redirection(t_cmd *cmd,
								t_redirection *new_redir);
t_cmd						*found_next_cmd(char *str, int *index);
void						add_next_cmd(t_cmd *cmd, t_cmd *next_cmd);

// utils
void						print_arguments(t_token *arg);
int							ft_isspace(char c);
void						free_tab(char **tab);

// pipe et redirection
void						exec_pipe(t_cmd *cmd);
void						exec_redir(t_cmd *cmd);
void						redir_stdout(int fd[2], t_cmd *next_cmd);
void						redir_stdin(int fd[2]);
void						redir_out(t_cmd *cmd, int fd);
void						redir_in(t_cmd *cmd, int fd);
void						redir_append(t_cmd *cmd, int fd);
void						redir_heredoc(t_cmd *cmd, int fd);
void						create_pipe(int fd[2], t_cmd *next_cmd);
void						gerer_process(pid_t pid, int fd[2],
								t_cmd **cur_cmd);
void						exec_process(t_cmd *cur_cmd, t_cmd *next_cmd,
								int fd[2]);
void						redir_stdout(int fd[2], t_cmd *next_cmd);
void						redir_stdin(int fd[2]);
char						**get_args(t_cmd *cmd);

char						*found_path(t_cmd *cmd);

// signaux
extern void					rl_replace_line(const char *text, int clear_undo);
void						config_signals(void);
void						gestionnaire(int sig);
#endif