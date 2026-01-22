#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 8192

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    int in_fd, out_fd;
    ssize_t n_read;
    
    if(argc != 3)
    {
        write(2, "Kullanim: ./program <kaynak> <hedef>\n", 38);
        return 1;
    }

    //KAYNAK DOSYA
    in_fd = open(argv[1], O_RDONLY);
    if(in_fd == -1)
    {
        perror("Kaynak dosya hatasi");
        return 2;
    }

    //HEDEF DOSYA
    out_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(out_fd == -1)
    {
        perror("Hedef dosya hatasi");
        return 3;
    }
    while((n_read = read(in_fd, buffer, BUFFER_SIZE)) > 0)
    {
        if(write(out_fd, buffer, n_read) != n_read)
        {
            write(2, "Yazma Hatasi\n", 14);
            return 4;
        }
    }
    close(in_fd);
    close(out_fd);
}