
## Sistemas Distribuídos – COS470 - 2024/1 
# Sinais
- Enunciando
* Trabalho Prático 1
-   Nesta tarefa você deve escrever dois programas distintos.
O primeiro programa deve ser capaz de enviar um sinal a qualquer outro processo. Este
programa recebe como parâmetros o número do processo destino e o sinal que deve ser
enviado. Seu programa deve verificar se o processo indicado pelo parâmetro existe, e
retornar um erro em caso caso negativo. Caso positivo, seu programa deve enviar o sinal
indicado.
- O segundo programa deve ser capaz de receber alguns sinais específicos. Para isto, você
precisa definir signal handlers. Seu programa deve capturar e reagir a três sinais diferentes
(de sua escolha), ou mais, imprimindo no terminal uma mensagem diferente para cada
sinal. Além disso, um dos sinais sendo capturados deve terminar a execução do programa,
ou seja, sua signal handler deve terminar o processo. Repare que após estipular as signal
handlers seu programa fica aguardando a chegada de sinais. Você deve implementar duas
formas de esperar, busy wait e blocking wait (passado como parâmetro para o programa).
Descubra como implementar cada um destas formas de fazer um processo esperar!
 Teste seus programas fazendo com que um envie sinais para o outro. Use também o
programa kill para enviar sinais para o seu segundo programa!


## Sinais utilizados
 SIGUSR1: 10.
 SIGUSR2: 12.
 SIGTERM: 15.

* Modo de Espera Bloqueante (Blocking Wait)

No modo de espera bloqueante, o processo fica inativo até que ocorra um evento específico (como a recepção de um sinal). Ele cede o controle do processador, permitindo que outros processos utilizem a CPU. Uma função comum usada para implementar a espera bloqueante é pause().
Características:

Eficiência de CPU: A CPU não é utilizada enquanto o processo está esperando. Isso é eficiente em termos de utilização de recursos.
Simples de implementar: Funções como pause() bloqueiam o processo até que um sinal seja recebido.

* Modo de Espera Ocupada (Busy Wait)

No modo de espera ocupado, o processo entra em um loop contínuo, verificando repetidamente se ocorreu um evento. Isso mantém a CPU ocupada, mesmo que não haja trabalho útil sendo realizado.
Características:

Consome CPU: O processo consome tempo de CPU constantemente, o que pode ser ineficiente, especialmente se houver muitos processos fazendo busy waiting.
Menor latência: Pode ter uma resposta ligeiramente mais rápida, pois o processo está sempre em execução e pronto para reagir imediatamente.


* Comparação

    Uso de CPU:
        Bloqueante: Utiliza CPU apenas quando necessário, liberando-a para outros processos enquanto espera.
        Ocupada: Mantém a CPU ocupada constantemente, mesmo enquanto espera, o que pode levar a um uso ineficiente da CPU.

    Complexidade:
        Bloqueante: Geralmente mais simples de implementar e entender.
        Ocupada: Pode ser simples de implementar, mas pode causar problemas de desempenho e consumo de energia.

    Latência:
        Bloqueante: Pode ter um ligeiro atraso na resposta, pois o processo precisa ser despertado.
        Ocupada: Responde imediatamente, pois está sempre ativo.


## Execução
    gcc -o <executavél> <nome_do_arquivo>

## Tipos de entrada 
* receive
    ./receive 0   # Para modo de espera bloqueante
     ./receive 1  # Para modo de espera ocupada

* send
     ./send <pid_do_proceso> <sinal>