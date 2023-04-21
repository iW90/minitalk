/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:07 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/20 20:37:40 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	print_letter(char *letter, int *bit, int *pid)
{
	if (*letter)
	{
		write (1, letter, 1);
		*bit = 7;
		*letter = 0;
	}
	else
	{
		write(1, "\n", 1);
		kill(*pid, SIGUSR2);
		*pid = 0;
		*bit = 0;
	}
}

static void	bit_receiver(int sig, siginfo_t *info, void *context)
{
	static char	letter;
	static int	bit;
	static int	pid;

	(void)context;
	if (!letter && !pid && !bit)
	{
		bit = 7;
		pid = info->si_pid;
	}
	if (sig == SIGUSR1)
		letter |= 1 << bit;
	else
		letter &= ~(1 << bit);
	bit--;
	if (bit < 0)
		print_letter(&letter, &bit, &pid);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_iggy;

	ft_printf("Server PID: %i\n", getpid());
	sigemptyset(&s_iggy.sa_mask);
	s_iggy.sa_handler = NULL;
	s_iggy.sa_flags = SA_SIGINFO;
	s_iggy.sa_sigaction = &bit_receiver;
	sigaction(SIGUSR1, &s_iggy, NULL);
	sigaction(SIGUSR2, &s_iggy, NULL);
	while (1)
		;
	return (0);
}
