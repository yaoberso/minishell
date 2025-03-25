#include "minishell.h"

void checkif2(char *str, char c)
{
    int count = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == c)
            count++;
        i++;
    }
    if (count % 2 != 0)
    {
        
        while (1)
        {
            char *line = readline("> ");
            if (line == NULL)
            {
                write(STDOUT_FILENO, "\n", 1);
                break;
            }
            if (line[0] == '\0')
            {
                free(line);
                continue;
            }
            free(line);
            if (val_ret == 130)
            {
                val_ret = 0;
                break;
            }
        }
    }
}


