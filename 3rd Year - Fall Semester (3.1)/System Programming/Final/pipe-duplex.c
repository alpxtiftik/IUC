#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    // İki boru tanımlıyoruz
    int p2c[2]; // Parent to Child (Parent yazar, Child okur)
    int c2p[2]; // Child to Parent (Child yazar, Parent okur)

    // İki pipe'ı da oluşturuyoruz
    pipe(p2c);
    pipe(c2p);

    pid_t p = fork();

    if (p == 0) { // Child Process
        close(p2c[1]);
        close(c2p[0]);

        char msg[50];
        read(p2c[0], msg, sizeof(msg));
        printf("Child, Parent dedi ki: %s\n", msg);

        char reply[] = "Tamam Parent aldim";
        write(c2p[1], reply, strlen(reply) + 1);

        close(p2c[0]);
        close(c2p[1]);
    }
    else { // Parent Process
        close(p2c[0]);
        close(c2p[1]);

        char msg[] = "Nasilsin Child";
        write(p2c[1], msg, strlen(msg) + 1);

        char reply[50];
        read(c2p[0], reply, sizeof(reply));
        printf("Parent, Child'dan cevap aldi: %s\n", reply);
        
		close(p2c[1]);
        close(c2p[0]);
    }
    return 0;
}
