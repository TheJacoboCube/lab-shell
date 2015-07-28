#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80
#define BUFFER_START 20

char * get_input();
void fail_with_error(const char * message);

int main(void)
{
    char * input, * args[(MAX_LINE/2) + 1];
    int should_run = 1;

    while(should_run) {
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
        
        if(fork() == 0)
        {
            execvp(args[0], args); // Execute command.
        }
    }

    return 0;
}

void fail_with_error(const char * message)
{
    printf("Error: %s", message);
    exit(0);
}

char * get_input()
{
    unsigned int bufferSize = BUFFER_START, bufferUsed = 0;
    char * buffer = calloc(bufferSize, sizeof(char));

    while (1) {
        char currentChar = getchar();

        if(currentChar == '\n')
        {
            break;
        }

        buffer[bufferUsed] = currentChar;

        if (bufferUsed == bufferSize - 1) { /* buffer full */
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
