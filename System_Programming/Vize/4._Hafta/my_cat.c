#include <unistd.h>

int main ()
{
    char buffer[4096];
    int n;

    while((n = read(0, buffer, sizeof(buffer))) > 0)
    {
        write(1, buffer, n);
    }
    
    return 0;
}