#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "cli.h"

int main (int argc, char* argv[])
{
    char* message_buffer = malloc(4096);

    if (argc == 1) // No message given
    {
        fprintf(stderr, "Usage: clog <message>\n");
        return -1;
    }

    cmdecho(argc, argv, message_buffer);

    free(message_buffer);

    return 0;
}
