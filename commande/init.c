#include "minishell.h"

t_env *init_env(char **envp)
{
    t_env *head = NULL;
    t_env *new;
    char *equal;
    int i = 0;

    while (envp[i])
    {
        equal = strchr(envp[i], '=');
        if (!equal)
        {
            i++;
            continue;
        }

        new = malloc(sizeof(t_env));
        if (!new)
        {
            free_env(head);
            return NULL;
        }

        new->name = strndup(envp[i], equal - envp[i]);
        new->value = strdup(equal + 1);
        if (!new->name || !new->value)
        {
            free(new->name);
            free(new->value);
            free(new);
            free_env(head);
            return NULL;
        }

        new->next = head;
        head = new;
        i++;
    }
    return head;
}

