#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void send(); // Ez fogja lekezelni a signal-t.

int main()
{
    int pfd[2]; //Pipe változó, a pfd[0]-ba írunk majd, a pfd[1]-ből olvasunk.
    pid_t child; //Gyermekprocessz azonosítója.

    if((pipe(pfd)) < 0 ) { //Létrehozzuk a csővezetéket, ha ez sikertelen, azaz 0-val tér vissza, akkor kiírjuk a hibát és visszatér a program 1-el.
        perror("pipe");
        return 1;
    }

    if((child=fork()) < 0) { //Létrehozzuk a gyermekprocesszt, ha sikertelen, akkor kiírjuk a hibát és visszatérünk egyel.
        perror("fork");
        return 1;
    }

    signal(SIGINT, send); //A SIGINT jelet(CTRL + C) a send fogja kezelni.

    if (child == 0) { //Ha a gyermekprocessz fut
        printf("Varom a  CTRL + C szignalt.\n");
        pause(); //Signal-t vár.
        printf("\nA szignal megerkezett.\n");
        close(pfd[0]); //Lezárjuk a felesleges vezetéket, mivel itt csak írni fogunk.
        write(pfd[1], "Kovacs Krisztian WIQPM2\n" , 23); //Beleírjuk az adatot.
        close(pfd[1]); //Lezárjuk.
        exit(0); //Kilépünk a child processzből.
    }
    else if (child > 0) { //Ha a szülőprocessz fut
        int returnStatus;
        waitpid(child, &returnStatus, 0); //Szülőprocessz megvárja míg lefut a gyermekprocessz. Akár azt is lehet vizsgálni, hogy hibátlan volt-e a futás, vagy nem. (ReturnStatus változóval)
        char s[1024]; //Ebbe tároljuk az adatot.
        close(pfd[1]); //Lezárjuk a felesleges vezetéket, mivel itt csak olvasni fogunk.
        printf("Az uzenet:\n");
        read(pfd[0], s, sizeof(s)); //Kiolvassuk az adatot.
        printf("%s", s); //Kiírjuk a szabványos kimenetre.
        close(pfd[0]); //Lezárjuk.
        exit(0); //Kilépünk a parent processzből.
    }

}

void send(){
    signal(SIGINT, SIG_DFL); // Bár nem kérte a feladat, visszaállítom az alapértelmezett signal kezelőt.
}
