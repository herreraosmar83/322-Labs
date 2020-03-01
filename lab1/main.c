#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/times.h>
//differnt functions in program
int forky();
int timer();
int procTimes();
int main(void){
    struct tms end_tms;
    timer(0);
    // starting time in seconds passed since 1970<- i dont know why
    //create child process here
    forky();
    // procTimes();
    times(&end_tms);
    clock_t cpu_time = end_tms.tms_cutime;
    clock_t utime = end_tms.tms_utime;
    clock_t stime = end_tms.tms_stime;
    clock_t cstime = end_tms.tms_cstime;

    printf("USER: %ld, ", cpu_time);
    printf("SYS: %ld \n", utime);
    printf("CUSER: %ld , ", stime);
    printf("CSYS: %ld, \n", cstime);
    // printf("USER: %ld, ", buf.tms_utime); 
    // printf("SYS: %ld \n", buf.tms_stime); 
    // printf("CUSER: %ld , ", buf.tms_cutime); 
    // printf("CSYS: %ld, \n", buf.tms_cstime); 
    
    //ENDING TIME of program SINCE 1970~ probably something to do with history
    timer(1);
    return(0); 
}
int forky(){
    int status;
    pid_t pid = fork();
    //fork tipically returns 1 or zero for parent or child process and -1 for an error.
    if(pid<0){
        perror("forking Failed");
    }
    //this is the child process
    else if(pid==0){
        //pid 
        printf("\nPID: %d,",(int)getpid());
        //ppid (parent id)
        printf(" PPID: %d\n",(int)getppid());
        sleep(2);
        exit(EXIT_SUCCESS);
    }
    //this is the parent process
    else{
        //process id 
        printf("PID: %d, ",(int)getpid());
        //the process id of parent to parent
        printf("PPID: %d, ", (int)getppid());
        //the process id of child (which should be the same as pid of child pid above for case 2)
        printf("CPID: %d, ",pid);
        waitpid(pid,&status,0);
        if (WIFEXITED(status)){
            int returned = WEXITSTATUS(status);
            printf("RETVAL %d\n",returned);
        }
        sleep(1);
    }
    return (0);
}
int timer(int val){
    time_t seconds; 
    seconds = time(NULL); 
    if(val==0){ //starting case
        printf("\nSTART: %ld", seconds);
    }
    else{//ending case
        printf("STOP: %ld  \n", seconds);
    }
    return (0);
}
int procTimes(){
    
      /* user time */
     /* system time */
     /* user time of children */
     /* system time of children */
     return(0);
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