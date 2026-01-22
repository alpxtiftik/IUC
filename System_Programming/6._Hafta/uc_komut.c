#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    //Komutların tam yolları(Absolute Paths)
    char *abspaths[] = 
    {
        "bin/echo",
        "bin/date",
        "bin/uname"
    };

    //Argüman dizileri
    char *args_echo[] = {"echo", "Merhaba sysprog!", NULL};
    char *args_date[] = {"date", NULL};
    char *args_uname[] = {"uname", -a, NULL};

    //Argüman dizilerini tek bir dizide toplama
    char **args[] = {args_echo, args_date, args_uname};

    int i;
    i = 0;
    while(i < 3)
    {   
        pid_t pid = fork();//Her komut için yeni process.
        if(pid < 0)
        {
            perror("fork() hatasi");
            return 1;
        }
        //CHILD PROCESS
        if(pid == 0)
        {
            printf("Ben Child Process. Komut %d calistiriliyor: %s\n", i+1, abspaths[i]);
            execv(abspaths[i], args[i]);
            
            //Komut buraya gelmemeli, gelirse execv hatasi.
            perror("execv() hatasi.");
            exit(1);
        }
        //PARENT PROCESS
        else
        {
            wait(NULL);
        }
        İ++
    }
    printf("Tum komutlar basariyla calistirildi.");
    return 0;
}

/*OZET ZAMAN CIZELGESİ:
parent fork -> child1 oluştur
child1 execv("/bin/echo", ...) -> /bin/echo çalışır; parent wait(NULL)
child1 tamamlanır (exit) -> parent wait döner
parent döngüde i++ -> fork -> child2 oluştur
child2 eXecv("/bin/date", ...) çalışır; parent wait eder
repeat for child3
tümü bittikten sonra parent printf("Tum komutlar...") ve exit*/



//_________________________________________________________________



/* 1) fork() EDILMEDEN ONCE 
init(1)
 └─ bash(1234)        <- senin shell'in (örnek PID)
     └─ sysprog(2000) <- senin çalıştırdığın program (parent)

*/

//_________________________________________________________________

/* 2) 1. fork() SONRASI
init(1)
 └─ bash(1234)
     └─ sysprog(2000)        # parent process
         └─ echo(2001)       # child1 execv("/bin/echo", ...)
*/

//_________________________________________________________________

/* 3) 1. CHILD BITTI, 2. CHILD CALISIRKEN
init(1)
 └─ bash(1234)
     └─ sysprog(2000)
         └─ date(2002)       # child2 execv("/bin/date", ...)

*/

//_________________________________________________________________

/* 4) 2. CHILD BITTI, 3. CHILD (SON) CALISIRKEN
init(1)
 └─ bash(1234)
     └─ sysprog(2000)
         └─ uname(2003)      # child3 execv("/bin/uname", ...)

*/

//_________________________________________________________________

/*5) TUM CHILD'LAR BITTIKTEN SONRA
init(1)
 └─ bash(1234)
     └─ sysprog(2000)   # parent döngüyü bitirip "Tum komutlar..." yazdıktan sonra exit yapar

*/