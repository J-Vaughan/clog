#include <stdio.h>
#include <string.h>

#include "cli.h"

int cmdecho (int argc, char* argv[], char* message_buffer)
{
    for (int i = 1; i < argc; i++)
    {
        strcat(message_buffer, argv[i]);
        if (i != argc - 1)
            strcat(message_buffer, " ");
    }

    if (printf("%lu: %s\n", (unsigned long) time(NULL), message_buffer) < 0)
        fprintf(stderr, "01: Couldn't echo message\n");

    return 0;
}

int confirm (const char* prompt)
{
    if (prompt != NULL)
    {
        printf("%s (y/n): ", prompt);
        if (fgetc(stdin) == 121)
        {
            putchar(10);
            return 0;
        } else
        {
            putchar(10);
            return -1;
        }
    } else
    {
        printf("(y/n): ");
        if (fgetc(stdin) == 121)
        {
            putchar(10);
            return 0;
        } else
        {
            putchar(10);
            return -1;
        }
    }
}
