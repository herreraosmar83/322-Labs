
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
    //assume if more than two arguements then a sigterm command has been entered so program will execute termination 
    // if(argc > 2)
    philosopher = argv[1];
    int value1;
    int value2;
    pid_t pid = getpid();
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
    return (0);
}
void think(int phil_num){
    printf("Philosopher #%d is thinking\n", phil_num);
    usleep(rand() % 5);
}
void eat(int phil_num){
    printf("Philosopher #%d is eating\n", phil_num);
    usleep(rand() % 5);
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