#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80

char * get_input()
{
    return "cat shell.c";
}

int main(void)
{
    char * input, * args[(MAX_LINE/2) + 1];
    int should_run = 1;

    while(should_run) {
        printf("stephen> ");
        fflush(stdout);

        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * (2) the child process will execvp()
        * (3) if command included &, parent will invoke wait()
        */

        input = get_input(); // Get input from user.
        args = strtok(input, " "); // Tokenize the args.

        // TODO: Check for ampersand.

        pid_t pid = fork();

        if(pid == 0)
        {
            execvp(args[0], args); // Execute command.
        }
    }

    return 0;
}
