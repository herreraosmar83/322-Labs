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
