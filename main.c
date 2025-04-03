/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/03 12:19:24 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int val_ret = 0;


int main(int argc, char **argv, char **envp)
{
    char            *input;
    struct termios  term;
    t_cmd           *cmd;
    t_env           *env_list;
    char            *prompt;

    (void)argc;
    (void)argv;
    env_list = init_env(envp);
    tcgetattr(STDIN_FILENO, &term);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
    while (1)
    {
        // Configurer les signaux pour le mode interactif
        config_signals();
        
        // Créer le prompt et lire l'entrée
        prompt = creat_prompt(env_list);
        input = readline(prompt);
        free(prompt);
        
        if (!input)
        {
            // Nettoyer avant de quitter
            free_env(env_list);
            printf("exit\n");
            break;
        }
        
        if (input[0] == '\0') {
            free(input);
            continue;  // Ignorer les commandes vides
        }
        
        // Ajouter à l'historique si non vide
        if (*input)
            add_history(input);
        
        // Allouer et initialiser une nouvelle structure cmd pour chaque commande
        cmd = malloc(sizeof(t_cmd));
        if (!cmd)
        {
            free(input);
            continue;  // Gestion d'erreur d'allocation
        }
        memset(cmd, 0, sizeof(t_cmd));  // Initialiser tous les champs à 0/NULL
        cmd->heredoc_fd = -1;
        
        // Parser la commande
        parsing(input, cmd, env_list);
        
        // Exécuter seulement si le parsing est réussi
        if (val_ret != 1)
            exec_pipe(cmd, env_list, envp);
        
        // Nettoyer les ressources
        free(input);
        free_cmd(cmd);  // Fonction à créer pour libérer toute la structure cmd
        val_ret = 0;    // Réinitialiser la valeur de retour pour la prochaine commande
    }
    
    return val_ret;
}
