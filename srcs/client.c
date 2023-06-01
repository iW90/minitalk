/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:10 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/01 10:48:55 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Variável Global
// "volátil" informa para o compilador que essa var será
// modificada com frequência e não deve ser otimizada.
// sig_atomic_t é um int, usada para portabilidade caso não seja mais um int.
volatile sig_atomic_t	g_flag = 1;

// Envia 1 e 0, sendo que 1 pelo SIGUSR1 e 0 vai pelo SIGUSR2
	// usleep está em ms (microsegundos)
	// Envia um bit por vez e aguarda o sinal (g_flag muda) para sair do looping
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

// Função para enviar mensagens para o server
	// acessando cada letra
	// acessando cada bit de cada letra
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

// Função flag para interromper o envio de bits quando a string terminar
	// Entra em "contato" com o server, pelo PID.
	// Envia o SIGUSR1 (10) como mensagem.
static void	await_flag(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)sig;
	g_flag = 0;
}

// Valida os argumentos e retorna o pid em int.
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

// sigemptyset:
	// Lida com sinais que devem ser ignorados.
	// Evita que outras aplicações interfiram, impedindo sinais externos.
// s_ggy.sa_handler:
	// [unused] Função padrão para lidar com sinal (recebe 1 parâmetro).
// s_iggy.sa_flags = SA_SIGINFO:
	// Altera o comportamento de um sinal.
	// siginfo determina que será usada a função de sa_sigaction.
// s_iggy.sa_sigaction = &await_flag:
	// Função para lidar com o sinal (recebe 3 parâmetros).
	// Não uso nenhum dos três, mas é obrigatório o formato.
// sigaction(SIGUSR1, &s_iggy, NULL):
	// Hook: Manipula o comportamento de um sinal.
int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	s_iggy;

	if (argc != 3)
		exit_program(1, "Invalid arguments.\n", 2);
	pid = pid_validator(argv[1]);
	sigemptyset(&s_iggy.sa_mask);
	s_iggy.sa_handler = NULL;
	s_iggy.sa_flags = SA_SIGINFO;
	s_iggy.sa_sigaction = &await_flag;
	sigaction(SIGUSR1, &s_iggy, NULL);
	message_sender(pid, argv[2]);
}

// TESTES E ANOTAÇÕES
	// O PID zero é reservado para o kernel.
	// Imprime 0 porque ^C é o kernel que envia.
	// SIGINT é o sinal de ^C (Ctrl+C).
