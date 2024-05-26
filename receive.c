#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig) {
    printf("Received SIGUSR1\n");
}

void handle_sigusr2(int sig) {
    printf("Received SIGUSR2\n");
}

void handle_sigterm(int sig) {
    printf("Received SIGTERM. Exiting...\n");
    exit(EXIT_SUCCESS);
}

void blocking_wait() {
    pause();
}

void busy_wait() {
    while (1) {
        sleep(1);
    }
}

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s <wait_mode>\n", prog_name);
    fprintf(stderr, "wait_mode: 0 for blocking wait, 1 for busy wait\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    int wait_mode = atoi(argv[1]);

    struct sigaction sa1, sa2, sa_term;

    sa1.sa_handler = handle_sigusr1;
    sa2.sa_handler = handle_sigusr2;
    sa_term.sa_handler = handle_sigterm;

    sigemptyset(&sa1.sa_mask);
    sigemptyset(&sa2.sa_mask);
    sigemptyset(&sa_term.sa_mask);

    sa1.sa_flags = 0;
    sa2.sa_flags = 0;
    sa_term.sa_flags = 0;

    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);
    sigaction(SIGTERM, &sa_term, NULL);

    printf("Waiting for signals...\n");

    if (wait_mode == 0) {
        blocking_wait();
    } else if (wait_mode == 1) {
        busy_wait();
    } else {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}