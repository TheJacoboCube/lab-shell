#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#define MAX_LINE 80
#define BUFFER_START 20

char * get_input();
void fail_with_error(const char * message);
void display_error(const char * message);
void execute(char ** args);

int main(void)
{
    char * input, * args;

    while(1) {
        printf("stephen> ");
        fflush(stdout);

        input = get_input(); // Get input from user.

        if(strlen(input) == 0)
        {
            free(input);
            continue;
        }

        args = strtok(input, " "); // Tokenize the args.
        free(input);

        // TODO: Check for ampersand.
        execute(&args);
    }

    return 0; // Buh-bye.
}

void display_error(const char * message)
{
    printf("\e[31mError: %s\n\e[0m", message); // Uh oh. Let the user know they screwed up.
}

void fail_with_error(const char * message)
{
    display_error(message);
    exit(1); // g2g
}

void execute(char ** args)
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        fail_with_error("Could not fork new process.");
    }
    else if(pid == 0)
    {
        if(execvp(*args, args) < 0) // Check execution success.
        {
            fail_with_error("Execution failed.");
        }
    }
    else
    {
        fail_with_error("Something went wrong.");
    }
}

char * get_input()
{
    unsigned int bufferSize = BUFFER_START, bufferUsed = 0; // Buffer tracking.
    char * buffer = calloc(bufferSize, sizeof(char)); // Hi, could I get a 00000000000000000000?

    while (1) {
        char currentChar = getchar(); // Dear user, Please press a button. Kthxbye.

        if(currentChar == '\n') // User be done.
            break; // gtfo

        buffer[bufferUsed] = currentChar;

        if (bufferUsed == bufferSize - 1) { // A little big there, champ?
            bufferSize *= 2; // Double the size.
            // Bigger buffer, please! :D
            buffer = (char *) realloc(buffer, bufferSize);

            if(buffer == NULL) // Aw, por que no?
            {
                fail_with_error("Could not get memory space for buffer.");
            }
        }

        bufferUsed++;
    }

    buffer[bufferUsed] = '\0'; // Zero string.

    return buffer;
}
