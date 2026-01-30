#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char * fifo_path = "kanal"; // FIFO dosyasının adı

    // mkfifo: Dosya sisteminde özel bir FIFO dosyası oluşturur.
    // 0666: Okuma/yazma izinleri
    mkfifo(fifo_path, 0666);

    // Yazma modunda aç (O_WRONLY).
    // DİKKAT: Karşı tarafta bir okuyucu bağlanana kadar bu satırda BLOKLANIR.
    int fd = open(fifo_path, O_WRONLY);

    if (fd < 0) {
        return 1; // Hata durumunda çıkış
    }

    char msg[] = "FIFO uzerinden selam";

    // Dosyaya yazar gibi pipe'a yaz
    write(fd, msg, strlen(msg) + 1);

    printf("Writer: Mesaj gönderildi.\n");

    close(fd);
    return 0;
}