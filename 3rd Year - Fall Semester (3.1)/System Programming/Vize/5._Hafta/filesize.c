#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> //open ve O_RDONLY için.

int main()
{
    int fd;
    off_t boyut;

    fd = open("a.txt", O_RDONLY);
    if(fd < 0)
    {
        perror("Dosya Acilamadi");
        return 1;
    }

    boyut = lseek(fd, 0, SEEK_END);

    if(boyut < 0)
    {
        perror("lseek Hatasi");
        return 2;
    }

    printf("a.txt'inin boyutu: %ld", (long)boyut);
    
    close(fd);

    return 0;
}