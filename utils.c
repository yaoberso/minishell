#include "minishell.h"

char *creat_prompt(t_env *env)
{
    char *pwd;
    char *prompt;
    size_t len;

    pwd = get_env_value(env, "PWD");
    if (!pwd) 
	{
        return NULL;
    }
    len = strlen(pwd) + 3;
    prompt = (char *)malloc(len * sizeof(char));
    if (!prompt) 
	{
        return NULL;
    }
    strcpy(prompt, pwd);
    strcat(prompt, "$ ");
    return prompt;
}