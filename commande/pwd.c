#include "minishell.h"

void ft_pwd()
{
	char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        exit(1);
    }
    printf("%s\n", cwd);
}
