#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handleSignal();

int main()
{
    signal(SIGINT, handleSignal);
    signal(SIGQUIT, handleSignal);

    for(int i = 0; i < 3; i++){
        pause();
    }
    return 0;
}

void handleSignal(int s){
    switch(s){
        case 2: {   //Int
            signal(SIGINT, SIG_DFL);
            printf("\n A CTRL + C kovetkezo lenyomasakor az alapertelmezett kezelo fog futni\n");
            break;
        }
        case 3: {   //Quit
            printf("\nAz elkapott jel: Quit\n");
            break;
        }
    }
}
