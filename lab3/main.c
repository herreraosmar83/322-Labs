#include <stdio.h>  
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>
int arguements;
char *inputs[];
int inputCount = 0;
int signals =0;
int sigterms = 0;
int sigHandle;
int signalToCatch;
char *properTerm[] = {"SIGHUP","SIGINT","SIGQUIT","SIGILL","SIGTRAP","SIGABRT","SIGIOT","SIGBUS","SIGFPE","SIGUSR1","SIGSEGV","SIGUSR2","SIGPIPE","SIGALRM","SIGTERM","SIGSTKFLT","SIGCHLD","SIGCONT","SIGTSTP","SIGTTIN","SIGTTOU","SIGURG","SIGXCPU","SIGXFSZ","SIGVTALRM","SIGPROF","SIGWINCH"};
char *term[] = {"HUP","INT","QUIT","ILL","TRAP","ABRT","IOT","BUS","FPE","USR1","SEGV","USR2","PIPE","ALRM","TERM","STKFLT","CHLD","CONT","TSTP","TTIN","TTOU","URG","XCPU","XFSZ","VTALRM","PROF","WINCH"};
void myhandle(int signum) {
    //reregister handled signal
    signal(signalToCatch,myhandle);
    time_t seconds; 
    seconds = time(NULL); 
    printf("\n %s caught at %ld\n", properTerm[signum-1],seconds);
    signals++;
    //  if 3 continous sigterm are caught then terminate with exit(EXIT_SUCCESS)
    if(signum == 15){
        sigterms++;
    }
    else
    {
        sigterms = 0;
    }
    
    if(sigterms == 3){
        printf("Total signals count: %d \n",signals);
        exit(EXIT_SUCCESS);
    }
}
int main(int args,char *argv[]){
    if(args<1){
        perror("failed");
    }
    else{
        pid_t pid = getpid();
        printf("commands entered:%d \n",args-1);
        // for(int i=1;i<args;i++){
        //     printf("%s, ",argv[i]);
        // }
        //emit pid
        fprintf(stderr,"\nPID: %d \n",(int)pid);
        //ASSIGN ARUGMENT TO PROPER SIGNAL TERM
        size_t sizeList = sizeof(properTerm)/sizeof(properTerm[0]);
        // printf("%ld\n",sizeList);
        //check for the proper term from list compared to command line input
        for(int i = 1;i<args;i++){
             for(int j=0;j<sizeList;j++){
                 //assign proper terms to execute
                 if(strcmp(argv[i],term[j]) == 0){
                    // printf("Adding %s to list\n",properTerm[j]);
                    inputs[inputCount] = properTerm[j];
                    inputCount++;
                    signalToCatch = j+1;
                    signal(signalToCatch, myhandle);
                 }
                 
             }
        }
        //pause continually
        while(1){
            pause();
        }
        //REGISTER HANDLER FOR EACH ARG sinal(2) and check for 3 continous sigterms to terminate program
        // for(int i = 0;i<args-1;i++){
        //     signal(15, myhandle);
        //     signal(1,myhandle);
        //     while(1){
        //         pause();
        //     }
        //     // end loop
        // }
        //pause continually


        


    }
    return (0);
}

/*
● The program processes the command line arguments
○ The arguments indicate which signals to catch
● The program emits a status line that includes its PID to stderr
● The program registers a handler for each argument (see signal(2))
● The program pauses itself continually (see pause(2))
● The handler registers itself again (read about unreliable signals)
● The handler emits a line to stdout that indicates
○ the signal caught, and
○ the time it was caught (see time(2))
● The program gracefully terminates after
○ receiving three successive SIGTERM signals (hint: static int count)
● The program emits a final status message to stderr that indicates
○ the number of signals caught

SIGKILL and SIGSTOP have been removed from the list of signals you should handle
   


SIGHUP
SIGINT
SIGQUIT
SIGILL
SIGTRAP
SIGABRT
SIGIOT
SIGBUS
SIGFPE
SIGUSR1
SIGSEGV
SIGUSR2
SIGPIPE
SIGALRM
SIGTERM
SIGSTKFLT
SIGCHLD
SIGCONT
SIGTSTP
SIGTTIN
SIGTTOU
SIGURG
SIGXCPU
SIGXFSZ
SIGVTALRM
SIGPROF
SIGWINCH
*/ 
