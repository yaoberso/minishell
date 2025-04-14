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
