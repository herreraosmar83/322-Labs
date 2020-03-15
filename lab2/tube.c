// In this software project, you are to write a command-line tool that launches two child processes,
// and sets up a pipe between them for inter-process communication. The general steps that this
// program undergoes include:
// ● The program allocates a pipe (see pipe(2))
// ● The program forks two children
// ● The parent process prints the PID of both children on stderr (see fprintf(3))
// ● The parent process closes access to the pipe and the child processes wires the
// pipe to allow for inter-process communication (see dup2(2))
// ○ via the standard stdout-stdin approach (see close(2))
// ● The first process executes the first command, and the second process executes
// the second command (see execve(2))
// ○ for the first iteration keep it simple — i.e., the child has no command line
// args
// ○ enhance your program to allow for an arbitrary number of command line
// args
// ● The program prints the return value of the first child and then the second child
// on stderr
#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
int forky();
int main(int args,char *command[]){
    printf("\nForking to creating pipe for two children:  \n");
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
        printf("\nchild process: \n");
        // ● The child process executes the supplied command (see execve(2))
        // ○ the child needs to prepare the new argv structure
        //take arguemements and execute the supplied arguemmnnts

        //concatenate all values of command line args
        int i;
        int v = 0;
        int size = args - 1;

        char *values = (char *)malloc(v);
        for(i = 1; i <= size; i++){
            values = (char *)realloc(values, (v + strlen(command[i])));
            strcat(values, command[i]);
            // strcat(values, " ");
        }
        printf("\nExecuting commands %s\n", values);
        char *arguements[] = {command[1],NULL};
        execve(values,arguements,NULL);
        sleep(1);
        exit(EXIT_SUCCESS);
    }//parent process
    else{
        // ● The parent process prints the PID of the child on stderr
        waitpid(pid,&status,0);
        printf("\nI am the parent\n");
        fprintf(stderr, "PID of Child: %d \n",pid); // Error message on stderr (using fprintf)
        if (WIFEXITED(status)){
            int returned = WEXITSTATUS(status);
            fprintf(stderr,"Return value of Child: %d\n",returned );      
        }
        sleep(1);
    }
    //prints out arguemnt 1
    return (0);
}