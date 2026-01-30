#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd; 
    off_t boyut; 

    if(argc != 2)
    {
        printf("Kullanim: ./%s <dosya_adi>\n", argv[0]);
        return 1;
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Dosya Acilamadi");
        return 1;
    }

    boyut = lseek(fd, 0, SEEK_END);
    
    printf("%s dosyasinin boyutu: %d", argv[1], boyut);
    
    close(fd);

    return 0;

}