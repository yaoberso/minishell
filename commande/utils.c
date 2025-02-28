#include "minishell.h"

char *get_env_value(t_env *env, const char *name)
{
	t_env *current;

	current = env;
	while(current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	printf("Variable '%s' not found\n", name); 
	return (NULL);
}

void set_env_value(t_env *env, const char *name, const char *new_value)
{
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
        {
            free(env->value);
            env->value = ft_strdup(new_value);
            return;
        }
        env = env->next;
    }
}