#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        perror("Fork Hatasi");
        return 1;
    }

    //CHILD
    if(pid == 0)
    {
        printf("Ben Child Process'im. Benim PID'im: %d\n", getpid());
        printf("Parent'ımın PID'i: %d", getppid());
    }

    //PARENT (PID > 0)
    else
    {
        wait(NULL);//PARENT, CHILD'I BEKLER.
        printf("Ben Parent Process'im. Benim PID'im: %d", getpid());
        printf("Child'ımın PID'i: %d", pid); //fork(), Child'ın PID'ini döndürür.
        printf("Parent'ımın PID'i: %d", getppid());
    }
    
    return 0;
}