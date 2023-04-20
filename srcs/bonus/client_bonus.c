/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:10 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/19 22:08:26 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t	g_flag = 1;

static void bit_sender(int pid, int bit)
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
		if(!*str)
			break ;
		str++;
	}	
}

static void	await_flag(int sig)
{
	g_flag = 0;
	if (sig = SIGUSR2)
		exit_program(0, "Pong!", 1);
}

static pid_t	pid_validator(char *pid)
{
	pid_t	pid;
	
	if (!ft_isalldigit(pid))
		exit_program(1, "Invalid arguments.\n", 2);
	pid = (pid_t)ft_atoi(pid);
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
	pid = pid_validator(argv[1])
	sigemptyset(&s_iggy.sa_mask);
	s_iggy.sa_handler = &await_flag;
	s_iggy.sa_flags = NULL;
	s_iggy.sa_sigaction = NULL;
	sigaction(SIGUSR1);
	sigaction(SIGUSR2);
	message_sender(pid, argv[2]);
	while (1)
		;
}

//echo -e '\xDF\xB7''\xF0\x9F\x98\x80''\xC3\xB8''\xE1\x8E\x88' | xargs ./client
//echo -e '\xF0\x9F\x98\x85''\xDF\xA6''\xE1\x8F\xA2''\xF0\x9F\x98\x8A' | xargs ./client