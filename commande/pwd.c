#include "minishell.h"

void ft_pwd(t_cmd *cmd)
{
	char *pwd;

    pwd = get_env_value(cmd->env, "PWD");
    if (pwd)
        printf("%s\n", pwd);
    else
        printf("PWD not set\n");
}
