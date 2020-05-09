#include <stdio.h>  
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
int main(int args,char *argv[]){
    if(args == 3){
        printf("\n number of seats: %s \nseat Number: %s \n",argv[1],argv[2]);
        semaphore chopstick [5];
    do {
        wait( chopstick[i] );
        wait( chopstick[ (i+1) % 5] );
        // .       .
        // .  EATING THE RICE
        // . 
        signal( chopstick[i] );
        signal( chopstick[ (i+1) % 5] );
        // .
        // . THINKING
        // .
    } while(1);       


    }
    else
    {
        perror("Not enough info");
    }
    return(0);
}