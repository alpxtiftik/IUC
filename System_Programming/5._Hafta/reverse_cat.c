#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;
    off_t size, i;
    char c;

    if(argc != 2)
    {
        printf("Kullanim: %s <dosya_adi>\n", argv[1]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        perror("open() Hatasi");
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);

    i = size - 1; 
    while(i >= 0)
    {
        lseek(fd, i, SEEK_SET);
        
        if(read(fd, &c, 1) == 1)
        {
            write(1, &c, 1);
        }
        i--;
    }

    close(fd);
    write(1, "\n", 1);
    return 0;
}