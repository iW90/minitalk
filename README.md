# 42 Cursus - minitalk

<img src="https://game.42sp.org.br/static/assets/achievements/minitalkm.png" alt="completion-with-bonus-badge" align="left">

O objetivo deste projeto é implementar um sistema de comunicação entre dois processos utilizando `sinais UNIX`. Para isso são criados dois programas, sendo um o **client** e o outro o **server**, e eles comunicarão entre si através do envio de sinais e mensagens. O **client** enviará uma mensagem (codificação binária), para o **server**, que a recebe, decodifica e exibe na tela. É permitido o uso apenas dos sinais `SIGUSR1` e `SIGUSR2`, e das funções `signal` e `sigaction`.

## Bônus <img src="https://img.shields.io/badge/GRADE-125%2F100-green" align="right">

O bônus apenas faz com que o server envie um sinal de volta ao client quando a mensagem for recebida, e o client imprime uma mensagem de sucesso.

## Compilação e Execução 

Para compilar a versão mandatória:

```
make
```

E para compilar a versão bônus:

```
make bonus
```

### Execução

Primeiramente é necessário executar o server no terminal:

```
./server
```

O programa continuará em execução para estar apto a receber mensagens.

Será exibida na tela uma numeração referente ao PID ("endereço" do server).

Abra outro terminal em paralelo e execute o client, enviando como parâmetro o PID gerado pelo server e a mensagem que deseja enviar:

```
./client 587 "Hello World!"
```

A mensagem será exibida no terminal onde o **server** está em execução.

Para encerrar o **server**, utilize o comando <kbd>Ctrl</kbd> + <kbd>C</kbd>.
