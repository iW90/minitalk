/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:10 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/13 21:10:32 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || \
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * negative);
}

// sig = SIGUSR1 || SIGUSR2
// info = PID e outros trens não usados
// [unused] context
void	siggyaction(int sig, siginfo_t *info, void *context)
{
	(void)context;
	printf("\n%i\n", info->si_pid);
	if (sig == SIGINT)
	{
		write(1, "hehehe\n", 7);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	s_iggy;

	if (argc != 3 /*|| ft_isdigit(argv[1])*/)
	{
		write(2, "Invalid arguments.\n", 19);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	printf("PID: %i\n", pid);

	// Lida com sinais que devem ser ignorados
	sigemptyset(&s_iggy.sa_mask);

	// [Unused] Função padrão para lidar com sinal (recebe 1 parâmetro)
	s_iggy.sa_handler = NULL;

	// Altera o comportamento de um sinal
	// siginfo determina que será usada a função de sa_sigaction
	s_iggy.sa_flags = SA_SIGINFO;

	// Função para lidar com o sinal (recebe 3 parâmetros)
	s_iggy.sa_sigaction = &siggyaction;

	// Hook: Manipula o comportamento de um sinal
	sigaction(SIGINT, &s_iggy, NULL);
	while (1)
		;
}
