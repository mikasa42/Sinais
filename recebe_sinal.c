#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void modo_uso(const char *nome_prog) {
    fprintf(stderr, " \nComo usar: %s <modo de espera>\n", nome_prog);
    printf("-------------------------------------- \n");  
    printf("Legenda: \n");
    printf("-------------------------------------- \n");                                                          
    printf("mode de espera: \n - 0 para espera bloqueante \n - 1 para espera ocupada \n");
    printf("-------------------------------------- \n");
}

void espera_bloqueante() {
    pause();
}

void espera_ocupada() {
    while (1) {
        sleep(100);
    }
}

/* SINAL 10*/
void sigusr1(int sig) {
    printf("Recebeu o sinal de usuário SIGUSR1\n");
}
/* SIGNAL 12 */
void sigusr2(int sig) {
    printf("Recebeu o sinal de usuário SIGUSR2\n");
}
/* SINAL 15*/
void sigterm(int sig) {
    printf("Recebeu o sinal SIGTERM. Execução terminada.\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso incorreto. Siga as instruções abaixo. \n");
        modo_uso(argv[0]);
        exit(EXIT_FAILURE);
    }

    struct sigaction sa1, sa2, sa_term;

    sa1.sa_handler = sigusr1;
    sa2.sa_handler = sigusr2;
    sa_term.sa_handler = sigterm;

    sigemptyset(&sa1.sa_mask);
    sigemptyset(&sa2.sa_mask);
    sigemptyset(&sa_term.sa_mask);

    sa1.sa_flags = 0;
    sa2.sa_flags = 0;
    sa_term.sa_flags = 0;

    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);
    sigaction(SIGTERM, &sa_term, NULL);

    printf("Aguardando sinais \n");

    int modo = atoi(argv[1]);

    if (modo == 0) {
        espera_bloqueante();
    } else if (modo == 1) {
        espera_ocupada();
    } else {
        modo_uso(argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}