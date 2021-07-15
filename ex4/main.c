//
// Created by think on 2021/7/8.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int global = 114514;

void halt() {
    __asm__("nop");
}

int main() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("PARENT | My PID: %d\n", getpid());
        printf("PARENT | My global variant is: %d\n", global);
        printf("PARENT | The address of my main() function: 0x%llx\n", (unsigned long long)&main);
        printf("PARENT | The address of my global variant: 0x%llx\n", (unsigned long long)&global);
        printf("PARENT | The address of my halt() function: 0x%llx\n", (unsigned long long)&halt);
        sleep(2);
        global = 1919;
        printf("PARENT | Modified global variant to %d\n", global);
        sleep(2);
        printf("PARENT | Child modified its global variant and mine is %d\n", global);
        sleep(1);
    } else if (pid == 0) {
        sleep(1);
        printf("CHILD  | My PID: %d\n", getpid());
        printf("CHILD  | My global variant is: %d\n", global);
        printf("CHILD  | The address of my main() function: 0x%llx\n", (unsigned long long)&main);
        printf("CHILD  | The address of my global variant: 0x%llx\n", (unsigned long long)&global);
        printf("CHILD  | The address of my halt() function: 0x%llx\n", (unsigned long long)&halt);
        sleep(2);
        printf("CHILD  | Parent modified its global variant and mine is %d\n", global);
        global = 810;
        printf("CHILD  | Modified global variant to %d\n", global);
    } else {
        perror("Fork failed.");
    }
    return 0;
}
