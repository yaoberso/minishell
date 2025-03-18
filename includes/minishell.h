/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:21:04 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/18 12:47:55 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int val_ret;

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


// structur qui ce met a jour a chaque deplasement dans les fichier
typedef struct s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
} t_env;

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
	char *heredoc_delim; // le delimiteur pour le heredoc "<<"
	struct s_redirection	*next;
}							t_redirection;

// Structure pour les commandes
typedef struct s_cmd
{
	char *cmd;  // pour les commandes
	t_token *arg; // liste chainé qui va contenir les arguments
	t_redirection   *redirection; // liste chainé qui va contenir les redirections
    struct s_cmd *next_cmd; // structure cree des qu un pipe est trouve
	struct s_cmd *prev_cmd; // structure cree des qu un pipe est trouve
	int save_stdin;
	int heredoc_fd;
} t_cmd;

// Fonction pour l'environement
void free_env(t_env *env);
t_env *init_env(char **envp);
void set_env_value(t_env *env, const char *name, const char *new_value);
char *get_env_value(t_env *env, const char *name);

// Fonction des commandes
void    ft_echo(t_token *current);
void    ft_pwd();
void    ft_cd(t_token *arg, t_env *env);
void    ft_env(t_env *env);
void    ft_export(t_token *arg, t_env **env);
void    ft_unset(t_token *arg, t_env **env);
void	cmd_exec(t_cmd *cmd, t_env *env);
void	exec_cmd_inter_exter(t_cmd *cmd, t_env *env);
int		is_cmd(char *cmd);

// Fonctions de parsing
void						add_token(t_token **head, t_token *new);
t_token						*new_token(char *str);
void						parsing(char *str, t_cmd *cmd, t_env *env);
char						*recup_token(char *str, int *index, t_env *env);
t_redirection				*found_redirection(char *str, int *index, t_env *env);
void						add_redirection(t_cmd *cmd,
								t_redirection *new_redir);
t_cmd						*found_next_cmd(char *str, int *index, t_env *env);
void						add_next_cmd(t_cmd *cmd, t_cmd *next_cmd);

// pipe et redirection
int	cmd_in_pipe(char *cmd);
void						exec_pipe(t_cmd *cmd, t_env *env, char **envp);
void						exec_redir(t_cmd *cmd);
void						redir_stdout(int fd[2], t_cmd *next_cmd);
void						redir_stdin(int fd[2]);
void						redir_out(t_cmd *cmd, int fd);
void						redir_in(t_cmd *cmd, int fd);
void						redir_append(t_cmd *cmd, int fd);
void						create_pipe(int fd[2], t_cmd *next_cmd);
void						gerer_process(pid_t pid, int fd[2],
								t_cmd **cur_cmd);
void						exec_process(t_cmd *cur_cmd,
								int fd[2], t_env *env, char **envp);
void						redir_stdin(int fd[2]);
char						**get_args(t_cmd *cmd);
int						redir_heredoc(t_cmd *cmd);
char						*found_path(t_cmd *cmd);
void 						apply_redirections(t_cmd *cmd);

// free
void						free_token(t_token *token);
void						free_redirection(t_redirection *redir);
void						free_cmd(t_cmd *cmd);
void						free_tab(char **tab);

// utils
char	*creat_prompt(t_env *env);
void 	print_arguments(t_token *arg);
int    ft_isspace(char c);

// signaux
extern void					rl_replace_line(const char *text, int clear_undo);
void						config_signals(void);
void						gestionnaire(int sig);
#endif