#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Benim PID'im: %d\n", getpid());
    printf("Parent Process PID'i: %d\n", getppid());

    return 0;
}