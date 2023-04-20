/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:07 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/19 21:14:23 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/*
static void	bit_receiver(int bit)
{
	
}
*/

// sig = SIGUSR1 || SIGUSR2
// info = PID e outros trens não usados
// [unused] context
static void	siggyaction(int sig, siginfo_t *info, void *context)
{
	(void)context;
	static char	letter;
	static int	bit;
	static int	pid;

	if (!letter && !pid && !bit)
	{
		bit = 7;
		pid = info->si_pid;
	}

	if (sig == SIGUSR1)
		letter |= 1 << bit;
	else //sig == SIGUSR2
		letter &= ~(1 << bit);
	bit--;
	if (bit < 0)
	{
		if (letter)
		{
			write (1, &letter, 1);
			bit = 7;
			letter = 0;
		}
		else
		{
			write(1, "\n", 1);
			pid = 0;
			bit = 0;
		}
	}
	kill(info->si_pid, SIGUSR1);

	// TESTE
	//if (sig == SIGUSR2)
	//	ft_printf("Client PID: %i\nSignal Received: %i\n", info->si_pid, sig);
}

int	main (void)
{
	struct sigaction	s_iggy;
	
	ft_printf("Server PID: %i\n", getpid());
	
	// Lida com sinais que devem ser ignorados.
	// Evita que outras aplicações interfiram, impedindo sinais externos.
	sigemptyset(&s_iggy.sa_mask);

	// [Unused] Função padrão para lidar com sinal (recebe 1 parâmetro).
	s_iggy.sa_handler = NULL;

	// Altera o comportamento de um sinal.
	// siginfo determina que será usada a função de sa_sigaction.
	s_iggy.sa_flags = SA_SIGINFO;

	// Função para lidar com o sinal (recebe 3 parâmetros).
	s_iggy.sa_sigaction = &siggyaction;

	// Hook: Manipula o comportamento de um sinal.
	// Comportamento dos sinais SIGUSR1 e SIGUSR2.
	sigaction(SIGUSR1, &s_iggy, NULL);
	sigaction(SIGUSR2, &s_iggy, NULL);

	// Mantém o server rodando.
	while (1)
		;
	return (0);
}

/* Imprime o binário do caractere
static void print_binary(char c)
{
	int i;

	for (i = 7; i >= 0; i--) {
		if (c & (1 << i)) {
			ft_printf("1");
		} else {
			ft_printf("0");
		}
	}
	ft_printf("\n");
}
*/