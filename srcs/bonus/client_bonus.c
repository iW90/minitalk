/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:10 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/20 21:25:57 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t	g_flag = 1;

static void	bit_sender(int pid, int bit)
{
	g_flag = 1;
	while (g_flag)
	{
		if (bit)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50000);
	}
}

static void	message_sender(int pid, char *str)
{
	int	bit;

	while (1)
	{
		bit = 8;
		while (bit--)
			bit_sender(pid, *str >> bit & 1);
		if (!*str)
			break ;
		str++;
	}
}

static void	await_flag(int sig)
{
	g_flag = 0;
	if (sig == SIGUSR2)
		exit_program(0, "Server message received!\n", 1);
}

static pid_t	pid_validator(char *p)
{
	pid_t	pid;

	if (!ft_isalldigit(p))
		exit_program(1, "Invalid arguments.\n", 2);
	pid = (pid_t)ft_atoi(p);
	if (pid < 1)
		exit_program(1, "Invalid arguments.\n", 2);
	return (pid);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	s_iggy;

	if (argc != 3)
		exit_program(1, "Invalid arguments.\n", 2);
	pid = pid_validator(argv[1]);
	sigemptyset(&s_iggy.sa_mask);
	s_iggy.sa_handler = &await_flag;
	sigaction(SIGUSR1, &s_iggy, NULL);
	sigaction(SIGUSR2, &s_iggy, NULL);
	message_sender(pid, argv[2]);
	while (1)
		;
}
