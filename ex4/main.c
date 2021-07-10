//
// Created by think on 2021/7/8.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("It is the parent process, PID: %d\n", getpid());
    } else if (pid == 0) {
        printf("It is the child process, PID: %d\n", getpid());
    } else {
        perror("Fork failed.");
    }
    return 0;
}