#include "minishell.h"

void	cmd_exec(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd->arg, env);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd->arg);
	// else if (ft_strcmp(cmd->cmd, "env") == 0)
	// 	ft_env(cmd->arg);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd->arg, &env);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd->arg, &env);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		printf("exit\n");
		exit (1);
	}
	else
	{
		printf("command not found\n");
		//il faudra free ici
		return ;
	}
}
