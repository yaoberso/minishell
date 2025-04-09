/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:21:04 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/09 11:27:28 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int					val_ret;

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# include <setjmp.h>
typedef struct s_signal
{
	int	in_heredoc;
	int in_execution;
}						t_signal;

// structur qui ce met a jour a chaque deplasement dans les fichier
typedef struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*next;
}							t_env;

// stucture en liste chainé qui va contenir tout les elements de la commande
typedef struct s_token
{
	char					*value;
	struct s_token			*next;
}							t_token;

// Structure pour les redirections
typedef struct s_redirection
{
	char *type;          // le type de redirection ça "<" ça ">" ou ça">>"
	char *file;          // le fichier de redirection
	char *heredoc_delim; // le delimiteur pour le heredoc "<<"
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_std
{
	int save_instd;
	int save_outstd;
	int original_stdin;
}							t_std;

// Structure pour les commandes
typedef struct s_cmd
{
	char *cmd;                  // pour les commandes
	t_token *arg;               // liste chainé qui va contenir les arguments
	t_redirection *redirection; // liste chainé qui va contenir les redirections
	struct s_cmd *next_cmd;     // structure cree des qu un pipe est trouve
	struct s_cmd *prev_cmd;     // structure cree des qu un pipe est trouve
	int						save_stdin;
	int						heredoc_fd;
	t_env					*env;
	t_std	*std;
}							t_cmd;


// Fonction pour l'environement
void						free_env(t_env *env);
t_env						*init_env(char **envp);
void						set_env_value(t_env *env, const char *name,
								const char *new_value);
char						*get_env_value(t_env *env, const char *name);

// Fonction des commandes
void						ft_echo(t_token *current);
void						ft_pwd(void);
void						ft_cd(t_token *arg, t_env *env);
void						ft_env(t_env *env);
void						ft_export(t_token *arg, t_env **env);
void						ft_unset(t_token *arg, t_env **env);
void						cmd_exec(t_cmd *cmd, t_env *env);
void						exec_cmd_inter_exter(t_cmd *cmd, t_env *env);
int							is_cmd(char *cmd);
void						print_env(t_env *env);
void						update_or_add_env(t_env **env, char *var_name,
								char *var_value);
void						add_env_variable(t_env **env, char *var_name,
								char *var_value);

// Fonctions de parsing
void						add_token(t_token **head, t_token *new);
t_token						*new_token(char *str);
void						parsing(char *str, t_cmd *cmd, t_env *env);
char						*recup_token(char *str, int *index, t_env *env);
t_redirection				*found_redirection(char *str, int *index,
								t_env *env);
void						add_redirection(t_cmd *cmd,
								t_redirection *new_redir);
t_cmd						*found_next_cmd(char *str, int *index, t_env *env);
void						add_next_cmd(t_cmd *cmd, t_cmd *next_cmd);
char						*sup_cote(char *str);
char						*sup_exp(char *str);
int							double_quote_with_simple_quote(char *str,
								int double_quote);
int						checkif2(char *str, char c);
char						*replace_exit_status(char *str, int start);
char						*extract_var_name(char *str, int start, int *end);
char						*replace_var_in_str(char *str, int start,
								char *var_value, int end);
char						*expand_var_at_position(char *str, int *pos,
								t_env *env);
char						update_quote_state(char current_char,
								char quote_state);
char						*expand_variables(char *str, t_env *env);
char						*initialize_process_quotes(char *str, int *j);
void						handle_quote_chars(char current_char,
								char *quote_state, char *result, int *j);
char						*process_quotes(char *str);
void						find_token_bounds(char *str, int *start, int *end,
								int *index);
char						*process_token(char *str_recup, t_env *env);
t_token						*new_token(char *str);
void						add_token(t_token **head, t_token *new);
void						add_redirection(t_cmd *cmd,
								t_redirection *new_redir);
void						add_next_cmd(t_cmd *cmd, t_cmd *next_cmd);
void						init_next_cmd(t_cmd *next_cmd);
int							check_pipe_syntax(char *str, int *index,
								t_cmd *next_cmd);
int							handle_cmd_token(t_cmd *next_cmd, char *str,
								int *index, t_env *env);
int							process_redirection(t_cmd *next_cmd, char *str,
								int *index, t_env *env);
int							process_pipe(t_cmd *next_cmd, char *str, int *index,
								t_env *env);
int							process_argument(t_cmd *next_cmd, char *str,
								int *index, t_env *env);
int							handle_cmd_start(t_cmd *next_cmd, char *str,
								int *index, t_env *env);
int							handle_token(t_cmd *next_cmd, char *str, int *index,
								t_env *env);
t_cmd						*found_next_cmd(char *str, int *index, t_env *env);
void						init_redirection(t_redirection *redir);
int							handle_heredoc(t_redirection *redir, char *str,
								int *index, t_env *env);
int							handle_input_redir(t_redirection *redir,
								int *index);
int							handle_output_redir(t_redirection *redir, char *str,
								int *index);
int							get_redir_file(t_redirection *redir, char *str,
								int *index, t_env *env);
int							count_non_var_chars(char *str);
void						fill_new_str(char *str, char *new_str);
char						*replace_variable(char *str, int start,
								char *var_value, int end);
int							skip_spaces(char *str, int i);
void						process_single_token(char *token, t_cmd *cmd);
void						processe_token(char *str, int *i, t_cmd *cmd,
								t_env *env);

// pipe et redirection
int							cmd_in_pipe(char *cmd);
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
void						exec_process(t_cmd *cur_cmd, int fd[2], t_env *env,
								char **envp);
void						redir_stdin(int fd[2]);
char						**get_args(t_cmd *cmd);
int							redir_heredoc(t_cmd *cmd);
char						*found_path(t_cmd *cmd, t_env *env);
void						apply_redirections(t_cmd *cmd);
int	exec_heredocs(t_cmd *cmd);
void restore_heredoc_stdin(t_cmd *cmd);

// pipe utils
void						create_pipe_in_exec(t_cmd *cur_cmd, int fd[2],
								int pipe_precedent);
int							command_not_found(t_cmd *cur_cmd,
								int pipe_precedent, int fd[2], t_env *env);
void						create_fork(pid_t pid, int pipe_precedent,
								t_cmd *cur_cmd, int fd[2]);
void						exit_status_process(int status);
void						check_fork(pid_t pid, int pipe_precedent,
								t_cmd *cur_cmd, int fd[2]);
void						dup_and_close_in_child(t_cmd *cur_cmd, int fd[2],
								int pipe_precedent);
void						close_pipe_precedent(int pipe_precedent);
void						check_fork(pid_t pid, int pipe_precedent,
								t_cmd *cur_cmd, int fd[2]);
void						create_process(t_cmd *cur_cmd, int fd[2],
								int pipe_precedent, pid_t pid);
void						exec_simple_cmd(t_cmd *cur_cmd, t_env *env);
void						child_process(t_cmd *cur_cmd, int fd[2],
								int pipe_precedent, char **envp, t_env *env);
int							parent_process(int *fd, int pipe_precedent,
								t_cmd *cur_cmd);
void						close_pipes(int fd[2]);
void						exec_builtin(t_cmd *cur_cmd, t_env *env,
								char *cmd_path);
char						*check_absolute_path(t_cmd *cmd, char **paths);
char						*search_in_paths(char **paths, char *cmd);

// free
void						free_token(t_token *token);
void						free_redirection(t_redirection *redir);
void						free_cmd(t_cmd *cmd);
void						free_tab(char **tab);

// utils
char						*creat_prompt(t_env *env);
void						print_arguments(t_token *arg);
int							ft_isspace(char c);
int is_only_spaces(const char *str);

// signaux
extern void					rl_replace_line(const char *text, int clear_undo);
void						config_signals(void);
void						gestionnaire(int sig);
void						config_signals_exec(void);
void						gestion_exec(int sig);
void						config_signals_heredoc(void);
void						gestion_heredoc(int sig);
void						restore_signals(void);

#endif