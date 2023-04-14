# FUNÇÕES

- [Signal](#signal-signalh)
- [Sigemptyset](#sigemptyset-signalh)
- [Sigaddset](#sigaddset-signalh)
- [Sigaction](#sigaction-signalh)
- [Getpid](#getpid-unistdh)
- [Kill](#kill-signalh)
- [Pause](#pause-unistdh)
- [Sleep](#sleep-unistdh)
- [Usleep](#usleep-unistdh)
- [Exit](#exit-stdlibh)

## Signal <signal.h>

A função `signal` executa uma função (ponteiro passado por parâmetro) quando um determinado sinal (inteiro passado por parâmetro) é enviado.

 `void (*signal(int sig, void (*func)(int)))(int);`

1. Retorna um ponteiro de função.
2. `sig` é o número do sinal.
3. `func` é o ponteiro para a função a ser executada.

Exemplo:

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int sig)
{
	printf("Recebido o sinal SIGINT.\n");
	exit(0);
}

int main()
{
	// Registrar o manipulador de sinal para SIGINT
	signal(SIGINT, sigint_handler);

	printf("Pressione Ctrl-C para gerar o sinal SIGINT.\n");

	// Loop infinito para manter o programa em execução
	while(1) {
		// Fazer nada
	}

	return (0);
}
```

## Sigemptyset <signal.h>

Usada para inicializar um conjunto vazio de sinais apontado por "set", ou seja, nenhum sinal é incluído no conjunto.

`int sigemptyset(sigset_t *set);`

1. `set` é um ponteiro para um conjunto de sinais do tipo `sigset_t`.
2. Retorna zero se for bem-sucedida ou -1 se ocorrer algum erro.

## Sigaddset <signal.h>

É usada para adicionar um sinal a um conjunto de sinais.

`int sigaddset(sigset_t *set, int signum);`

1. `set` é um ponteiro para um conjunto de sinais do tipo `sigset_t`.
2. `signum` é o número do sinal que será adicionado ao conjunto.
3. Retorna zero se for bem-sucedida ou -1 se ocorrer algum erro.

Exemplo:

```c
#include <stdlib.h>
#include <signal.h>

int main()
{
	sigset_t set;

	// Inicializar o conjunto de sinais vazio
	sigemptyset(&set);

	// Adicionar o sinal SIGINT ao conjunto
	sigaddset(&set, SIGINT);

	// Fazer algo que pode gerar um sinal SIGINT

	return (0);
}
```

## Sigaction <signal.h>

É usada para manipular o comportamento de um sinal.

`int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

1. `signum` é o número do sinal que será adicionado ao conjunto.
2. `act` é um ponteiro para uma estrutura do tipo "sigaction" que especifica a nova ação a ser tomada quando o sinal ocorrer.
3. `oldact` é um ponteiro para uma estrutura do tipo "sigaction" que receberá a ação anterior para o sinal.
4. Retorna zero se for bem-sucedida ou -1 se ocorrer algum erro.

Estrutura do tipo `sigaction`:

```c
struct sigaction {
	void (*sa_handler)(int);
	void (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t sa_mask;
	int sa_flags;
	void (*sa_restorer)(void);
};
```

- `sa_handler`: um ponteiro para a função de tratamento do sinal. Quando um sinal ocorre, o sistema chama essa função para manipulá-lo.
	- Se "sa_handler" for definido como `SIG_IGN`, o sinal será ignorado.
	- Se "sa_handler" for definido como `SIG_DFL`, o comportamento padrão para o sinal será usado.
- `sa_sigaction`: um ponteiro para a função de tratamento do sinal que recebe três argumentos:
	- o número do sinal
	- um ponteiro para uma estrutura "siginfo_t" que contém informações adicionais sobre o sinal.
	- um ponteiro para dados adicionais. Essa função é chamada em vez de "sa_handler" se o sinal tiver o sinalizador SA_SIGINFO definido em "sa_flags".
- `sa_mask`: um conjunto de sinais adicionais que serão bloqueados enquanto o manipulador de sinal estiver sendo executado.
- `sa_flags`: sinalizadores que alteram o comportamento do tratamento do sinal. Alguns dos sinalizadores disponíveis são SA_SIGINFO, SA_RESTART e SA_NODEFER.
- `sa_restorer`: um ponteiro para uma função de restauração de pilha. Geralmente não é usado.

é frequentemente usada para personalizar o comportamento de sinais específicos. Por exemplo, o seguinte trecho de código define uma função de tratamento de sinal personalizada para o sinal SIGINT:

Exemplo:

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigint(int sig)
{
	printf("Recebido o sinal SIGINT.\n");
	exit(0);
}

int main()
{
	struct sigaction sa;

	// Configurar o manipulador de sinais para SIGINT
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	// Fazer algo que pode gerar um sinal SIGINT

	return (0);
}
```

## Getpid <unistd.h>

Essa função é usada para obter o ID do processo atual. O processo é uma instância de um programa em execução no sistema operacional e é identificado exclusivamente pelo seu ID de processo (PID).

`pid_t getpid(void);`

1. Não requer nenhum parâmetro.
2. Retorna o PID do processo que o chamou.

## Kill <signal.h>

É usada para enviar um sinal para um processo específico. O sinal pode ser usado para notificar o processo sobre um evento ou solicitar que ele execute uma determinada ação.

Frequentemente é usada em conjunto com a função "getpid" para enviar sinais para o próprio processo.

`int kill(pid_t pid, int sig);`

1. `pid` é o ID do processo que receberá o sinal.
2. `sig` é o número do sinal que será enviado.
3. Retorna zero se for bem-sucedida ou -1 se ocorrer algum erro.

Alguns sinais que podem ser enviados como `sig`:

- `SIGTERM`: solicita que o processo encerre com graça.
- `SIGKILL`: força o processo a encerrar imediatamente.
- `SIGSTOP`: suspende a execução do processo.
- `SIGCONT`: retoma a execução do processo após a suspensão.

Exemplo:

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* Neste exemplo, a função "getpid" é usada para obter o ID do processo atual.
 * A função "kill" é usada para enviar o sinal SIGTERM para o próprio processo.
 * Se ocorrer algum erro ao enviar o sinal, a função "perror" é usada para
 * imprimir uma mensagem de erro.
 */
int main()
{
	// Obter o ID do processo atual
	pid_t pid = getpid();

	// Enviar o sinal SIGTERM para o processo atual
	int result = kill(pid, SIGTERM);
	if (result != 0) {
		perror("kill");
		return 1;
	}

	return 0;
}
```

## Pause <unistd.h>

É usada para suspender a execução de um programa até que um sinal seja recebido. Ela fica em espera até que um sinal seja recebido pelo processo, nesse momento ela retorna o valor -1 e o sinal é tratado por uma rotina previamente definida.

`int pause(void);`

1. Não requer nenhum parâmetro.
2. Retorna -1 após receber um sinal e executar a rotina de tratamento de sinal correspondente.
	- Antes de receber um sinal, ela bloqueia a execução do programa.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* Neste exemplo, a função "signal" é usada para definir uma rotina
 * de tratamento de sinal personalizada para o sinal SIGINT.
 * A função "pause" é usada para suspender a execução do programa até que o
 * sinal seja recebido e a rotina de tratamento de sinal seja executada.
 * Quando o sinal é recebido, a função "handle_sigint" é executada,
 * que simplesmente imprime uma mensagem na tela.
 * Depois que a rotina de tratamento de sinal é executada, a função
 * "pause" retorna e a execução do programa é retomada.
 */
void handle_sigint(int sig) {
	printf("Received SIGINT signal.\n");
}

int main() {
	// Definir uma rotina de tratamento de sinal personalizada para SIGINT
	signal(SIGINT, handle_sigint);

	printf("Waiting for SIGINT signal...\n");

	// Suspender a execução do programa até que um sinal seja recebido
	pause();

	printf("Program resumed after receiving a signal.\n");

	return 0;
}
```

## Sleep <unistd.h>

Suspende a execução de um programa por um determinado número de segundos. Ela pode ser usada para adicionar atrasos no código ou para limitar a taxa de execução do programa.

`unsigned int sleep(unsigned int seconds);`

1. `seconds` é o tempo em segundos que o processo ficará dormindo.
2. A função retorna zero após o tempo especificado ter decorrido. 
	- Se um sinal for recebido pelo processo durante o tempo de espera, a função pode retornar um valor menor que o tempo especificado.

```c
#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Iniciando atraso...\n");
	sleep(5);
	printf("Atraso concluído.\n");
	return 0;
}
```

## Usleep <unistd.h>

Suspende a execução de um programa por um determinado número de microssegundos (1 microssegundo = 1/1000000 segundos). Ela é semelhante à função "sleep", mas permite uma resolução mais fina, permitindo a suspensão da execução em intervalos menores que um segundo.

`int usleep(useconds_t usec);`

1. `usec` é o tempo em microsegundos que o processo ficará dormindo.
2. A função retorna zero após o tempo especificado ter decorrido.
	- Se um sinal for recebido pelo processo durante o tempo de espera, a função pode retornar um valor menor que o tempo especificado.

```c
#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Iniciando atraso em microssegundos...\n");
	usleep(500000); //0,5 segundos
	printf("Atraso concluído.\n");
	return 0;
}
```

## Exit <stdlib.h>

Termina a execução do programa. Ela é usada para indicar ao sistema operacional que o programa foi concluído com sucesso ou com erro e para retornar um valor de status para o processo pai.

`void exit(int status);`

1. Status se refere ao erro ou sucesso da execução.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
	int resultado = 42;
	printf("Terminando o programa...\n");
	exit(resultado);
}
```
