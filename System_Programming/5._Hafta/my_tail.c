#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) 
{
    int fd;
    off_t end_pos, start_pos;
    long n_bytes;
    char buffer[BUF_SIZE];
    int n_read;

    if (argc !=3)
    {
        dprintf("Kullanim: ./%s <dosya_adi> <N>", argv[1]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        perror("Dosya acilamadi.");
        return 2;
    }

    end_pos = lseek(fd, 0, SEEK_END);
    if(end_pos < 0)
    {
        perror("lseek() hatasi.");
        return 3;
    }
    
    n_bytes = atol(argv[2]);

    if(end_pos > n_bytes)
    {
        start_pos = end_pos - n_bytes;
    }
    else
    {
        start_pos = 0;
    }

    lseek(fd, start_pos, SEEK_SET);

    while((n_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(1, buffer, n_read);
    }
    
    close(fd);
    return 0

}
