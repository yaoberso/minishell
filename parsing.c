/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/02/20 19:55:46 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// regroupe les fonctions de parsing
void	parsing()
{
	
}

// le cas ou il y'a un seul argument entre guillemets
void	pars_one_arg(char *str, t_cmd *cmd)
{
	cmd->cmd = ft_split(str, ' ');
}

// le cas ou il y'a plusieurs arguments
void pars_mult(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\0')
			break ;
	}
}