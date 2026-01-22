#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if(pid1 < 0)
    {
        perror("fork() hatasi.");
        return 1;
    }

    //CHILD PROCESS
    if(pid1 == 0)
    {
        printf("Ben Child Process (PID: %d), Parent'ım PID: %d", getpid(), getppid());
        //CHILD'IN CHILD'INI OLUŞTURMA (TORUN)
        pid2 = fork();
        if(pid2 < 0)
        {
            perror("fork() hatasi");
            return 2;
        }
        //CHILD'IN CHILD'I (TORUN) PROCESS 
        if(pid2 == 0)
        {
            printf("Ben Torun (Child'ın Child'ı) Process (PID: %d), Parent'ım(Child) PID: %d", getpid(), getppid());
        }
        //CHILD PROCESS
        else
        {
            wait(NULL);//CHILD, CHILD'I BİTENE KADAR BEKLER.
            printf("Torun tamamlandi. Child cikiyor.");
        }
    }
    //PARENT PROCESS
    else 
    {
        wait(NULL);
        printf("Child tamamlandi. Parent cikiyor.");
    }
    return 0;
}