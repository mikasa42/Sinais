#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s <pid> <signal_number>\n", prog_name);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = (pid_t) atoi(argv[1]);
    int sig = atoi(argv[2]);

    if (kill(pid, 0) == -1) {
        if (errno == ESRCH) {
            fprintf(stderr, "Process with PID %d does not exist.\n", pid);
        } else {
            perror("Error checking PID");
        }
        exit(EXIT_FAILURE);
    }

    if (kill(pid, sig) == -1) {
        perror("Error sending signal");
        exit(EXIT_FAILURE);
    }

    printf("Signal %d sent to process %d.\n", sig, pid);
    return 0;
}
