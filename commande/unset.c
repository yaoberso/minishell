#include "minishell.h"

#include "minishell.h"

void	ft_unset(t_token *arg, t_env **env)
{
	t_token	*current_arg;
	t_env	*current;
	t_env	*prev;
	t_env	*tmp;

	current_arg = arg;
	while (current_arg)
	{
		current = *env;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->name, current_arg->value) == 0)
			{
				tmp = current->next;
				if (prev)
					prev->next = tmp;
				else
					*env = tmp;
				free(current->name);
				free(current->value);
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		current_arg = current_arg->next;
	}
}
