#include "minishell.h"

void ft_echo(t_token *current)
{
    int newline;
    t_token *arg;

    newline = 1;
    arg = current;
    if (!arg)
    {
        write(1, "\n", 1);
        return;
    }
    while (arg && ft_strncmp(arg->value, "-n", 2) == 0)
    {
        int i = 2;
        while (arg->value[i] == 'n')
            i++;
        if (arg->value[i] == '\0')
        {
            newline = 0;
            arg = arg->next;
        }
        else
            break;
    }
    while (arg != NULL)
    {
        write(1, arg->value, ft_strlen(arg->value));
        if (arg->next)
            write(1, " ", 1);
        arg = arg->next;
    }

    if (newline)
        write(1, "\n", 1);
}
