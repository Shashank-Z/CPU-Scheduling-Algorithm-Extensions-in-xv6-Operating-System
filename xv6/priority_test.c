#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(1, "Usage: priority_test <number_of_processes>\n");
        exit();
    }

    int total_low_priority = atoi(argv[1]);
    if (total_low_priority < 1) {
        printf(1, "Please provide at least 1 low-priority process.\n");
        exit();
    }

    int pid;

    // Create a high-priority process
    pid = fork();
    if (pid == 0) {
        printf(1, "Low-priority process started (PID: %d).\n", getpid());
        chpr(getpid(), 15); // higher value -> lower priority
        volatile double x = 0;
        for (volatile long long i = 0; i < 10000000; i++) {
            x = x + 6.66 * 45.45;
        }
        printf(1, "Low-priority process completed (PID: %d).\n", getpid());
        exit();
    } else if (pid < 0) {
        printf(1, "Failed to fork low-priority process.\n");
        exit();
    }

    // Wait for some time before creating low-priority processes
    sleep(50);

    // Create multiple low-priority processes
    for (int i = 0; i < total_low_priority; i++) {
        pid = fork();
        if (pid == 0) {
            printf(1, "High-priority process started (PID: %d).\n", getpid());
            chpr(getpid(), 5); // lower value -> higher priority
            volatile double x = 0;
            for (volatile long long j = 0; j < 100000; j++) {
                x = x + 6.66 * 45.45;
            }
            printf(1, "High-priority process completed (PID: %d).\n", getpid());
            exit();
        } else if (pid < 0) {
            printf(1, "Failed to fork High-priority process.\n");
            exit();
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i <= total_low_priority; i++) {
        wait();
    }

    exit();
}
