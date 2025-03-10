#include "minishell.h"

char *creat_prompt(char *cwd)
{
	char *prompt;
	int i;

	i = 0;
	prompt = malloc(sizeof(char) * ft_strlen(cwd) + 3);
	while(i < (ft_strlen(cwd)))
	{
		prompt[i] = cwd[i];
		i++;
	}
	prompt[i] = '$';
	i++;
	prompt[i] = ' ';
	return (prompt);
}