/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:10 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/17 21:41:43 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Variável Global
// "volátil" informa para o compilador que essa var será modificada com frequência e não deve ser otimizada.
// sig_atomic_t é um int, usada para portabilidade caso não seja mais um int.
volatile sig_atomic_t	g_flag = 1;


// Envia 1 e 0, sendo que 1 pelo SIGUSR1 e 0 vai pelo SIGUSR2
// usleep está em ms (microsegundos)
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

	while (1) //acessando cada letra
	{
		bit = 7;
		while (bit >= 0) //acessando cada bit de cada letra
		{
			bit_sender(pid, (*str >> bit) & 1);
			bit--;
		}
		if(!*str)
			break ;
		str++;
	}	
}

static void	siggyaction(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	g_flag = 0;
	ft_printf("Sig: %i\n", sig);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	s_iggy;

	if (argc != 3 || !ft_isalldigit(argv[1]))
	{
		write(2, "Invalid arguments.\n", 19);
		return (-1);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	if (pid < 1)
	{
		write(2, "Invalid arguments.\n", 19);
		return (-1);
	}
	ft_printf("PID: %i\n", pid);

	// Lida com sinais que devem ser ignorados.
	// Evita que outras aplicações interfiram, impedindo sinais externos.
	sigemptyset(&s_iggy.sa_mask);

	// Função padrão para lidar com sinal (recebe 1 parâmetro).
	s_iggy.sa_handler = NULL;

	// Altera o comportamento de um sinal.
	// siginfo determina que será usada a função de sa_sigaction.
	s_iggy.sa_flags = SA_SIGINFO;

	// [Unused] Função para lidar com o sinal (recebe 3 parâmetros).
	s_iggy.sa_sigaction = &siggyaction;

	sigaction(SIGUSR1, &s_iggy, NULL);
	message_sender(pid, argv[2]);

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