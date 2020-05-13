
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define SEM_FILE1 "/PhilChop_1"
#define SEM_FILE2 "/PhilChop_2"


bool value = true;
int philosopher;
int signalCounter;
void think(int philospher);
void eat(int philosopher);
void myhandle(int signum) {
    //reregister handled signal
    value = false;
    time_t seconds; 
    seconds = time(NULL); 
    printf("caught SIGETERM at %ld seconds\n",seconds);
    fprintf(stderr, "Philosopher #%d had %d turns\n", philosopher, signalCounter);
    exit(EXIT_SUCCESS);
    
}

int main(int argc, char *argv[]){   
    pid_t pid = getpid();
    //assume if kill has been entered so program will execute termination 
    if(strcmp(argv[1],"kill") == 0){
         //kills process hopefully 
        int pidToKill = atoi(argv[3]);
        kill(pidToKill,SIGTERM);
        printf("value %s",argv[1]);
   
    }
    else{
        philosopher = atoi(argv[1]); //atoi to cast properly
        int value1;
        int value2;
        sem_t *chopstick_1 = sem_open(SEM_FILE1, O_CREAT, 0666, 1);
        sem_t *chopstick_2 = sem_open(SEM_FILE2, O_CREAT, 0666, 1);
        fprintf(stderr,"\nPID: %d \n",(int)pid);
        sem_getvalue(chopstick_1, &value1);
        sem_getvalue(chopstick_2, &value2);
        signal(SIGTERM,myhandle);
        while (value){
            sem_wait(chopstick_1);
            sem_wait(chopstick_2);
            // philosopher should be eating 
            eat(philosopher);
        
            sem_post(chopstick_1);
            sem_post(chopstick_2);
            // philosopher should be thinking
            think(philosopher);
            signalCounter++;
        };
        sem_close(chopstick_1);
        sem_close(chopstick_2);
        sem_unlink(SEM_FILE1);
        sem_unlink(SEM_FILE2);    
    }
    
    return (0);
}
void think(int philosopher){
    printf("Philosopher #%d is thinking\n", philosopher);
    usleep(rand() % 5000000);
}
void eat(int philosopher){
    printf("Philosopher #%d is eating\n", philosopher);
    usleep(rand() % 5000000);
}

//semaphore chopstick [5];
//     do {
//         wait( chopstick[i] );
//         wait( chopstick[ (i+1) % 5] );
//         // .       .
//         // .  EATING THE RICE
//         // . 
//         signal( chopstick[i] );
//         signal( chopstick[ (i+1) % 5] );
//         // .
//         // . THINKING
//         // .
//     } while(1);       
// cd ../mnt/c/Users/herre/Documents/322/322-Labs/lab4