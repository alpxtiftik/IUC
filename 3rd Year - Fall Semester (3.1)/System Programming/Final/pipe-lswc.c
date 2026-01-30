#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];

    // Pipe oluştur
    pipe(fd);

    pid_t p = fork();

    if (p == 0) { // Child Process (ls çalıştıracak)
        close(fd[0]);

        // Standart Output'u (1), Pipe'ın yazma ucuna (fd[1]) yönlendir
        // Artık printf veya ls'in çıktıları ekrana değil, pipe'a gidecek.
        dup2(fd[1], STDOUT_FILENO);

        // Yönlendirme yapıldığı için fd[1]'in kendisine ihtiyaç kalmadı
        close(fd[1]);

        // ls komutunu çalıştır. Bu noktada child process'in hafızası ls koduyla değişir.
        execlp("ls", "ls", NULL);
    }
    else { // Parent Process (wc çalıştıracak)
        // Yazma ucunu kapat, wc girdiyi okuyacak
        close(fd[1]);

        // Standart Input'u (0), Pipe'ın okuma ucuna (fd[0]) yönlendir
        // Artık scanf veya wc'nin girdileri klavyeden değil, pipe'tan gelecek.
        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);

        // wc -l komutunu çalıştır
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}
