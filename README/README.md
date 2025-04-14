# minishell

![alt text](<Screenshot from 2025-02-20 13-25-26.png>)



- valeur de retour
- faire la gestion des signaux selon la ou on se trouve et adapte
- afficher le conitrole C quqnd on quitte
- exit code au milieu des signaux qui doit donner une autre valeur je crois
qund tu control c dans un cat par exemple tu dois avoir un exit code different


tests speciaux

cat | cat | ls

export PIPE="|"
echo $PIPE




pouvoir executer minishell dans minishell et faire controle c


- gerer cd avec plusieurs arguments pareil pour les autres commandes internes a voir ya
- ajouter les valeurs de retour fonction interne ya

<!-- - regler la double sortie "/home/nadahman/Desktop/minishell$ /home/nadahman/Desktop/minishell$" quqnd je ctrl c ou autre nas # je pense qu il faut integrer les signaux dans les redirections a voir
- faut que apres les redirections sa soit un fichier valide sinon gerer -->

- controle heredoc ya
- faire que controle z ne fasse rien ya



- gerer variable expansion guillemet simple : echo '$USER' ya

<!-- - gerer ca export VAL="|" nas
- tester bien les pipes et les redirections nas
- les sorties d erreeurs doivent etre bien ecris et gerer 
- faire la gestion des signaux selon la ou on se trouve et adapter en fonction
- lancer minishell dans minishell sans tout casser et control c -->

-leaks
-norminette





27-03

    /home/nadahman/Desktop/minishell$ cat | bash: syntax error near unexpected token `|' faire comme pour les redirections

    regarder le parsing pour "|" quqnd y a un caractere avant les guillemets

tester tout ca et faire fonctionner correctement, ou attendre d etre a lecole pour tester sur l ordi labas echo salut | exit echo salut | export

avec l ancienne versiion ca fonctionne, a voir ce que j ai fais

il faudra allouer la structure data

02-04

    <!-- gerer espace -->
    mettre un message d erreur qund on exit avec des arguments
    gerer la valeur de retour pou commande interne
    <!-- export | ls et ls | export a gerer -->
    <!-- la variable PATH ne se suprime pas avec unset -->



03-04
<!-- - voir si c est export ou non le probleme -->
<!-- - pareil pour env "ls | env" est cense donne env    -->
<!-- - faire le path -->
- heredoc doit s ouvrir avec << et rien avant faire en sorte de rajouter cat devant si il n yest pas deja 

<!-- - corriger les segfaults /mnt/c/users/nasim/desktop/minishell$ <
bash: syntax error near unexpected token `newline'
/mnt/c/users/nasim/desktop/minishell$ < ls
[34]    117184 segmentation fault (core dumped)  ./minishell                    // a cause du malloc dans le main 
revoir comment je l avais corriger avant
et tester ducoup commande avec redirections etc
- Test << redirection (il n'est pas nécessaire de mettre à jour l'historique). -->

<!-- - quand je test des espaces vides ou tabs et qu ensuite je fais entree lorsque je test une commande ca ne l execute pas -->

- expr $? + $

- controle C dans les cat sans arguments grep qqchose ou redirection

- ca "ls | grep c | wc -l" ne fait rien mais en bash il ecris command not found dans le notre

<!-- - ls | export doit fonctionner et montrer export -->

<!-- - tester redirection dans pipe et comparer avec bash -->

<!-- - quand je fais entrer ca ecris un M retester cat cat ls -->


07-04

- regarder a l ecole si j ai le soucis de double free quand je fais "cat >>" ou autre
- regarder aussi les fd non fermer et les fermer
- expansion dans heredoc ?
- close fd regarder leaks




09-04 
<!-- 
- toujours sa /home/nadahman/Desktop/minishell$ cat <<
bash: syntax error near unexpected token `newline'
/home/nadahman/Desktop/minishell$ cat >>
bash: syntax error near unexpected token `newline'
free(): double free detected in tcache 2
[8]    28922 IOT instruction (core dumped)  ./minishell -->
<!-- - revoir le val_ret pour l erreur de cat << >> -->


12-04

- fd a fermer quand controle c dans heredoc
- check des leaks complet
- tests complet
- norminette

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
int heredoc_parent(pid_t pid, int heredoc_fd[2]);
int init_heredoc(t_cmd *cmd, int heredoc_fd[2]);
int fork_heredoc(t_cmd *cmd, int heredoc_fd[2]);
int handle_heredoc_error(t_cmd *cmd, int heredoc_fd[0], int status);
int check_heredoc_status(t_cmd *cmd, int heredoc_fd[2], pid_t pid);
int finalize_heredoc(t_cmd *cmd, int heredoc_fd[2]);

#include "minishell.h"

int heredoc_parent(pid_t pid, int heredoc_fd[2])
{
	int status;
	
	close(heredoc_fd[1]);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		close(heredoc_fd[0]);
		return (1);
	}
	if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(heredoc_fd[0]);
		return (1);
	}
	if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(heredoc_fd[0]);
		return (1);
	}
	close(heredoc_fd[0]);
	return (0);
}

int init_heredoc(t_cmd *cmd, int heredoc_fd[2])
{
	cmd->save_stdin = dup(STDIN_FILENO);
	if (cmd->save_stdin == -1)
	{
		perror("dup");
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	if (heredoc_pipe(heredoc_fd) != 0)
	{
		close(cmd->save_stdin);
		cmd->save_stdin = -1;
		return (-1);
	}
	return (0);
}

int fork_heredoc(t_cmd *cmd, int heredoc_fd[2])
{
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(heredoc_fd[0]);
		close(heredoc_fd[1]);
		close(cmd->save_stdin);
		cmd->save_stdin = -1;
		restore_signals();
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		if (cmd->save_stdin >= 0)
			close(cmd->save_stdin);
		heredoc_child(cmd, heredoc_fd);
	}
	return (pid);
}

int handle_heredoc_error(t_cmd *cmd, int heredoc_fd[0], int status)
{
	close(heredoc_fd[0]);
	dup2(cmd->save_stdin, STDIN_FILENO);
	close(cmd->save_stdin);
	cmd->save_stdin = -1;
	restore_signals();
	return (-1);
}

int check_heredoc_status(t_cmd *cmd, int heredoc_fd[2], pid_t pid)
{
	int status;
	
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (handle_heredoc_error(cmd, heredoc_fd[0], status));
	}
	if (WIFSIGNALED(status))
	{
		val_ret = 130; // SIGINT
		return (handle_heredoc_error(cmd, heredoc_fd[0], status));
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		val_ret = WEXITSTATUS(status);
		return (handle_heredoc_error(cmd, heredoc_fd[0], status));
	}
	return (0);
}

int finalize_heredoc(t_cmd *cmd, int heredoc_fd[2])
{
	if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (handle_heredoc_error(cmd, heredoc_fd[0], 0));
	}
	close(cmd->save_stdin);
	close(heredoc_fd[0]);
	restore_signals();
	return (0);
}

int redir_heredoc(t_cmd *cmd)
{
	pid_t pid;
	int heredoc_fd[2];
	int ret;
	
	if (init_heredoc(cmd, heredoc_fd) != 0)
		return (-1);
	
	pid = fork_heredoc(cmd, heredoc_fd);
	if (pid == -1)
		return (-1);
	else if (pid > 0)
	{
		close(heredoc_fd[1]);
		ret = check_heredoc_status(cmd, heredoc_fd, pid);
		if (ret != 0)
			return (ret);
		return (finalize_heredoc(cmd, heredoc_fd));
	}
	
	return (0);
}