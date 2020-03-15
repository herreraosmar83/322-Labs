#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int forky();
int main(int args,char *command[]){
    printf("\nForking to creat a child process:  \n");
    forky(args,command);
    return (0);
}
int forky(int args,char *command[]){
    int status;
    pid_t pid = fork();
    //fork tipically returns 1 or zero for parent or child process and -1 for an error.
    if(pid<0){
        perror("The forking Failed");
    }
    //this is the child process
    else if(pid==0){
        //pid 
        printf("\n child process: \n");
        // ● The child process executes the supplied command (see execve(2))
        // ○ the child needs to prepare the new argv structure
        //take arguemements and execute the supplied arguemmnnts
        
        // assume more than one arguement is passed 
        if(args>1){
            char *argsV[args];
            for(int i=1;i<args;i++){
                int val = i-1;
                printf("%d",val);
                argsV[val] = command[i];
                printf("\n--------\n");
                execve(argsV[val],argsV,NULL);
            }

            printf(argsV[0]);

        }
        sleep(1);
        exit(EXIT_SUCCESS);
    }//parent process
    else{
        // ● The parent process prints the PID of the child on stderr
        printf("\nI am the parent\n");
        fprintf(stderr, "PID of Child: %d\n",pid); // Error message on stderr (using fprintf)
        waitpid(pid,&status,0);
        if (WIFEXITED(status)){
            int returned = WEXITSTATUS(status);
            fprintf(stderr,"\nReturn value of Child: %d\n",returned );      
        }
        sleep(1);

    }
    
    
    //prints out arguemnt 1
    return (0);
}


// In this software project, you are to write a command-line tool that launches another process and
// then have this process execute a particular program. The general steps that this program
// undergoes include:
// ● The program forks a child process (see fork(2))
// ● The parent process prints the PID of the child on stderr
// ● The child process executes the supplied command (see execve(2))
// ○ the child needs to prepare the new argv structure
// ● The parent prints the return value of the child on stderr (see waitpid(2))