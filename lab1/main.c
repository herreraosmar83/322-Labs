#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
int forker();
int main(){
    // time in seconds passed since 1970<- i dont know why
    time_t seconds; 
    seconds = time(NULL); 
    printf("Start: %ld", seconds);


//create child process here
    forker();

    //print out the process id of parent

    //print out the process id of child 
    printf(" \nPPID: %d", (int)getpid());
    printf(", PID: some value");

    printf("\nPPID: some value");
    printf(", PID: some value");
    printf(", CPID: some value");
    printf(", RETVAL: some value");

    printf("\nUSER: some value");
    printf(", SYS: some value");

    printf("\nCUSER: some value");
    printf(", CSYS: some value");

    printf("\nSTOP: some value"); 
    return(0); 
}
int forker(){

    pid_t pid = fork();

    if(pid<0){
        perror("forking Failed");
    }
    else if(pid==0){
        //this is the child process

        //pid 
        printf("child pid: %d",getpid());
        //ppid (parent id)
        printf("\n parent ppid: %d",getppid());
        sleep(2);
        exit(EXIT_SUCCESS);
    }
    else{
        //this is the parent process

        //process id 
        printf("\n parent PID: %d",getpid());
        //the process id of parent to parent
        printf("\nparent PPID: %d", getppid());
        //the process id of child (which should be the same as pid of child pid above for case 2)
        printf("\nChild CPID: %d",pid);
        wait(NULL);

    }
    return (0);
}





/* 
START: 1410281230
PPID:26485, PID: 26846
PPID:26484, PID: 26485, CPID: 26846, RETVAL: 0
USER: 233354, SYS: 2334455
CUSER:234434, CSYS: 233223
STOP: 1410281240

● The program prints the number of seconds since.. (see time(2))
● The program creates a child process (see fork(2))
● The program will wait for the child to finish (see waitpid(2))
● The program and its child reports on the information
○ The process ID of its parent (see getppid(2))
○ Its own process ID (see getpid(2))
○ The process ID of its child (if applicable) (see fork(2))
○ The return status of its child (if applicable) (see exit(3), waitpid(2))
● The program will report the following time information (see times(2))
○ user time
○ system time
○ user time of child
○ system time of child
*/