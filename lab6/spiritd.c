#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/resource.h>
pid_t mole;


void term_signal_handler(int signum);
void usr_signal_handler(int signum);

int main()
{
    // set a clear file creation mask to 0
    umask(0);
    pid_t pid = fork();
    //CREATE fork process and check for parent proecess.. exit
    if (pid == 1){ //parent ptocess is one
        exit(EXIT_SUCCESS);
    }
    //create a new sessioin  process group 
    pid_t sid = setsid();

    //change dirtectory 
     printf("%s\n", getcwd(s, 100));///gives current dir
     chdir("/");



}


// part one:
// These coding standards include:
// 1. Set the file creation mask to 0 (see umask(2))
// 2. Fork and have the parent exit (see fork(2))
// 3. Create a new session (see setsid(2))
// a. create a new process group
// 4. Change the current working directory to be “/” (see chdir(2))
// 5. Close all unneeded file descriptors (see getrlimit(2))
// 6. Reopen the standard file descriptors to map to /dev/null (see dup(2))
// When the program is running, it will respond to external stimuli (i.e., signals).

/* 
part two
● The daemon handles: SIG_TERM, SIG_USR1, and SIG_USR2 (see signal(2))
● Upon SIG_TERM, the program kills all child processes and
shutdowns the daemon gracefully. (see kill(2))
● Upon SIG_USR1, the program will
○ kill child process #1 (mole1)
○ randomly create either mole1 or mole 2 if it does not already exists
● Upon SIG_USER2, the program will
○ kill child process #1 (mole2)
○ randomly create either mole1 or mole 2 if it does not already exists
● When a new mole is created the following steps are followed:
○ fork a new process (see fork(2))
○ randomly determine the child process number (either 1 or 2)
○ exec the program mole,
with the value of argv[0] set to either (see execv(2))
■ mole1
■ mole2



*/ 