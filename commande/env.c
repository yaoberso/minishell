#include "minishell.h"

void ft_env(t_env *arg)
{
	t_env *current;

	current = arg;
	while (current)
	{
		printf("%s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
}