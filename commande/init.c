#include "minishell.h"

t_env *init_env(char **envp)
{
    t_env *head = NULL;
    t_env *new;
    char *equal;
    int i = 0;

    while (envp[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return NULL;
        
        equal = strchr(envp[i], '=');
        new->name = strndup(envp[i], equal - envp[i]);
        new->value = strdup(equal + 1);
        new->next = head;
        head = new;

        i++;
    }
    return head;
}
