#include "minishell.h"

void ft_echo(t_token *current)
{
	int newline;
	t_token *arg;

	newline = 1;
	arg = current;
	if (arg == NULL || arg->next == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	while (arg && ft_strcmp(arg->value, "-n") == 0)
	{
	   newline = 0;
	   arg = arg->next;
	}
	while(arg)
	{
		printf("%s", arg->value);
		if(arg->next != NULL)
			write(1, " ", 1);
		arg = arg->next;
	}
	if(newline)
		write(1, "\n", 1);
}
