#include <stdio.h>  
#include <stdlib.h>
#include <signal.h>
int arguements;
char *inputs[];
int main(int args,char *argv[]){
    if(args<1){
        perror("failed");
    }
    else{
        printf("Number of commands:%d \n",args);
        for(int i=1;i<args;i++){
            printf("command[%d]:%s\n",i,argv[i]);
        }
        printf("exiting");
        return (0);
    }
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



*/ 
