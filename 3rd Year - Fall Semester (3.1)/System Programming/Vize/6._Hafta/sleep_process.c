#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        perror("fork() hatasi.");
        return 1;
    }

    if(pid == 0)
    {
        sleep(2);
        printf("Ben Child (PID: %d), 2 saniye sleep() attım ve geldim.\n", getpid());
    }
    
    else
    {
        printf("Ben Parent (PID: %d), Child'ı bekliyorum.", getpid());
        wait(NULL);//CHILD'IN BİTİŞİNİ BEKLER.
        printf("Child tamamlandi. Parent cikiyor...");
    }

    return 0;
}