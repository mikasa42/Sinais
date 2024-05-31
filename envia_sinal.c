#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void print_usage(const char *nome_prog) {
    fprintf(stderr, "Como usar: %s <pid> <número do sinal>\n", nome_prog);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso incorreto. Siga as instruções abaixo. \n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = (pid_t) atoi(argv[1]);
    int sig = atoi(argv[2]);

    if (kill(pid, 0) == -1) {
        if (errno == ESRCH) {
            fprintf(stderr, "O processo %d não existe.\n", pid);
        } else {
            perror("Não foi possível verificar o PID");
        }
        exit(EXIT_FAILURE);
    }

    if (kill(pid, sig) == -1) {
        perror("Erro no envio do sinal.");
        exit(EXIT_FAILURE);
    }

    printf("Sinal %d enviado para o processo %d.\n", sig, pid);
    return 0;
}
