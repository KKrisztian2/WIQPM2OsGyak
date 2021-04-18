#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int child;

    mkfifo("WIQPM2", S_IRUSR | S_IWUSR);

    child=fork();
    if(child>0){
        char s[1024];
        int fd;

        fd=open("WIQPM2", O_RDONLY);
        read(fd, s, sizeof(s));
        printf(" %s ", s);

        close(fd);
        unlink("WIQPM2");
    }
    else if(child == 0){
        int fd;

        fd=open("WIQPM2", O_WRONLY);
        write(fd, "KK WIQPM2!\n", 12);
        close(fd);
    }

}
