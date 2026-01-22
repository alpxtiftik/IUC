#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int status = 0;

    printf("Ana program basliyor...\n");

    pid = fork();

    if(pid < 0)
    {
        perror("Fork hatasi");
        return 1;
    }
    if(pid == 0)
    {
        printf("Ben Child Process'im (PID: %d).\n", getpid());
        printf("'ls' programina donusuyorum...\n");
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);

        //BURAYA GELMEMELİ GELİYORSA HATALI
        perror("execvp() hatasi.");
        exit(1);
    }
    else
    {
        printf("Ben Parent Process'im. Child'ın bitmesini bekliyorum (Child PID: %d).\n", pid);
        waitpid(pid, &status, 0);

        if(WIFEXITED(status))
        {
            printf("Child bitti. ")
        }
    }
}