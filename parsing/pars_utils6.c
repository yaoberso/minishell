#include "minishell.h"

// // Helper function for recup_token to find token boundaries
// static void find_token_bounds(char *str, int *start, int *end, int *index)
// {
//     int i;
//     char current_quote = 0;
    
//     i = *index;
//     while (str[i] && ft_isspace(str[i]))
//         i++;
//     if (!str[i])
//     {
//         *start = i;
//         *end = i;
//         *index = i;
//         return;
//     }
//     *start = i;
//     while (str[i] && ((!ft_isspace(str[i]) || current_quote) && 
//           ((str[i] != '<' && str[i] != '>' && str[i] != '|') || current_quote)))
//     {
//         if (!current_quote && (str[i] == '\'' || str[i] == '"'))
//             current_quote = str[i];
//         else if (current_quote && str[i] == current_quote)
//             current_quote = 0;
//         i++;
//     }
//     *end = i;
//     *index = i;
// }

// // Process token after extraction
// static char *process_token(char *str_recup, t_env *env)
// {
//     char *result;
    
//     if (!str_recup)
//         return (NULL);
//     checkif2(str_recup, '"');
//     checkif2(str_recup, '\'');
//     result = expand_variables(str_recup, env);
//     free(str_recup);
    
//     if (!result)
//         return (NULL);
//     result = process_quotes(result);
//     return (result);
// }