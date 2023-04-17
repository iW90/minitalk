/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:10 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/16 21:34:57 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	siggyaction(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)sig;
	ft_printf("Hehehe");
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	s_iggy;

	if (argc != 3 /*|| ft_isdigit(argv[1])*/)
	{
		write(2, "Invalid arguments.\n", 19);
		return (-1);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	ft_printf("PID: %i\n", pid);

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




	/* TESTS AND NOTES*/
	// Entra em "contato" com o server, pelo PID.
	// Envia o SIGUSR1 (10) como mensagem.
	//kill(pid, SIGUSR1);

	// Hook: Manipula o comportamento de um sinal.
	//sigaction(SIGINT, &s_iggy, NULL);
	//while (1)
	//	;
}

// sig = SIGUSR1, SIGUSR2, SIGINT, etc.
// info = PID e outros trens não usados.
// [unused] context.
/*
static void	siggyaction(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	// O PID zero é reservado para o kernel.
	// Imprime 0 porque ^C é o kernel que envia.
	// SIGINT é o sinal de ^C (Ctrl+C).
	//ft_printf("\n%i\n", info->si_pid);
	
	// Se o sig (sinal) recebido for igual a SIGINT (^C)
	if (sig == SIGINT)
	{
		write(1, "hehehe\n", 7);
		exit(0);
	}
}
*/