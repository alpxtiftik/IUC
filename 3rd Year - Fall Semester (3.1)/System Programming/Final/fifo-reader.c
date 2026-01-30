#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    const char * fifo_path = "kanal";

	mkfifo(fifo_path, 0666);
    // Okuma modunda aç (O_RDONLY)
    // Writer bağlanana kadar burası da bekleyebilir.
    int fd = open(fifo_path, O_RDONLY);
    if (fd < 0) {
        return 1;
    }

    char buf[100];

    // FIFO'dan oku
    int n = read(fd, buf, sizeof(buf));
	if(n > 0)
	{
		printf("Reader: Gelen mesaj > %s", buf);
	}
	else 
	{
		printf("Reader: FIFO bos veya kapatildi.");
	}

    close(fd);
    return 0;
}
