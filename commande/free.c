#include "minishell.h"

void free_env(t_env *env)
{
	t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->name);
        free(env->value);
        free(env);
    	env = tmp;
    }
}