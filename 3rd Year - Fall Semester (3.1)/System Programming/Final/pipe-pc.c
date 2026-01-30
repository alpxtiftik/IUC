#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    // File descriptor dizisi:
    // fd[0] -> okuma (read) ucu
    // fd[1] -> yazma (write) ucu
    int fd[2];
    char buffer[50];
	 
    pipe(fd);
    pid_t p = fork();

    if (p == 0) { // Child Process
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Child: gelen mesaj: %s\n", buffer);
        close(fd[0]);
    }
    else { // Parent Process
        close(fd[0]);
        char msg[] = "Merhaba child";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }

    return 0;
}
