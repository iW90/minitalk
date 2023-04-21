/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:11:07 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/20 21:18:28 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Imprime cada letra montada pelo bit_receiver.
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
		*pid = 0;
		*bit = 0;
	}
}

// Função que recebe cada bit e monta a letra
	// Quando o bit é -1, uma letra foi montada e é enviada para impressão.
	// sig = SIGUSR1 || SIGUSR2
	// info = PID e outros trens não usados
	// [unused] context
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
	// Comportamento dos sinais SIGUSR1 e SIGUSR2.
// O looping infinito mantém o programa rodando até usar um Ctrl^C.
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

/* TESTES E ANOTAÇÕES
// Imprime o binário do caractere
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