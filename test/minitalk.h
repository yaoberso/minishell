/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:22:34 by nadahman          #+#    #+#             */
/*   Updated: 2025/01/07 13:22:34 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "printf/ft_printf.h"

/*# define BUFFER_SIZE 1
# define SIGUSR1 10
# define SIGUSR2 12*/

typedef struct s_signal
{
	int		pid;
	char	*message;
}	t_signal;

void	sigusr1_handler(int signum);
void	sigusr2_handler(int signum);
void	send_signal(int pid, char c);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
void	ft_memcpy(char *dest, const char *src, size_t n);

#endif