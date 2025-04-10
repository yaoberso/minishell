#include "minishell.h"

char	*creat_prompt(t_env *env)
{
	char	*pwd;
	char	*prompt;
	size_t	len;

	pwd = get_env_value(env, "PWD");
	if (!pwd)
	{
		return (NULL);
	}
	len = strlen(pwd) + 3;
	prompt = (char *)malloc(len * sizeof(char));
	if (!prompt)
	{
		return (NULL);
	}
	strcpy(prompt, pwd);
	strcat(prompt, "$ ");
	return (prompt);
}
int is_only_spaces(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isspace(str[i]) && str[i] != '"' && str[i] != '\'')
            return (0);
        i++;
    }
    return (1);
}