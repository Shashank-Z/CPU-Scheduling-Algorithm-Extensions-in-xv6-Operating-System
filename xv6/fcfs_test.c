#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(1, "Usage: fcfs_test <number_of_processes>\n");
        exit();
    }

    int total_processes = atoi(argv[1]);
    if (total_processes % 2 != 0) {
        printf(1, "Provide an even number of processes.\n");
        exit();
    }

    int half = total_processes / 2; // Half for long processes, half for short processes
    int pid;

    // Create long-running processes
    for (int i = 0; i < half; i++) {
        pid = fork();
        if (pid == 0) {
            printf(1, "Long-running process started (PID: %d).\n", getpid());
            volatile double x = 0;
            for (volatile int j = 0; j < 10000000; j++) { // 10 million iterations
                x = x + 3.14 * 2.71; // Consume CPU time
            }
            printf(1, "Long-running process completed (PID: %d).\n", getpid());
            exit();
        } else if (pid < 0) {
            printf(1, "Failed to fork long-running process.\n");
            exit();
        }
    }

    // Create short-running processes
    for (int i = 0; i < half; i++) {
        pid = fork();
        if (pid == 0) {
            printf(1, "Short-running process started (PID: %d).\n", getpid());
            for (volatile int j = 0; j < 100000; j++) { // 100,000 iterations
                // Minimal CPU usage
            }
            printf(1, "Short-running process completed (PID: %d).\n", getpid());
            exit();
        } else if (pid < 0) {
            printf(1, "Failed to fork short-running process.\n");
            exit();
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i < total_processes; i++) {
        wait();
    }

    exit();
}
