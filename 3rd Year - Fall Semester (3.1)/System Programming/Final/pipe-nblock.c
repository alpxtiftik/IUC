#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> // File Control kütüphanesi

int main() {
    int fd[2];
    pipe(fd);

    // Fork yapmıyoruz, tek süreçte gösterim.

    // Pipe'ın okuma ucunu NONBLOCK (Bloklanmaz) olarak ayarla
    // F_SETFL: File Set Flag (Dosya bayrağını ayarla)
    fcntl(fd[0], F_SETFL, O_NONBLOCK);

    char buffer[20];

    // Pipe boş. Normalde burada program donardı.
    // Ancak O_NONBLOCK sayesinde hata (-1) döndürüp hemen devam eder.
    int n = read(fd[0], buffer, sizeof(buffer));

    if (n < 0) {
        // Beklenen durum: Veri yok hatası
        perror("Non-blocking read sonucu");
    } else {
        printf("Okunan veri: %d\n", n);
    }

    return 0;
}
