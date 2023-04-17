/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:07 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/16 21:35:00 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// sig = SIGUSR1 || SIGUSR2
// info = PID e outros trens não usados
// [unused] context
static void	siggyaction(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR2)
		ft_printf("Client PID: %i\nSignal Received: %i\n", info->si_pid, sig);
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