/* LICENSE AND CONTACT INFORMATION * * * * * * * * * * * * * * * * * * * * * * *
 * CLog, a logging tool written in C                                           *
 * Copyright (C) 2017 James Vaughan                                            *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                             *
 * You can contact me at dev.jamesvaughan@gmail.com with any questions         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "save.h"

int parsemessage (int argc, char* argv[], char* buffer)
{
    for (int i = 1; i < argc; i++)
    {
        strcat(buffer, argv[i]);
        if (i != argc - 1)
        {
            strcat(buffer, " ");
        }
    }

    return 0;
}

int savemessage (char* buffer)
{
    FILE* logfile;
    char* filename = "log/logfile";
    char* unixtime;

    unixtime = malloc(16);

    if (sprintf(unixtime, "%lu: ", (unsigned long) time(NULL)) < 0)
    {
        fprintf(stderr, "Couldn't time\n");
        return -5;
    }

    if (mkdir("log", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0)
    {
        printf("./log directory created\n");
    }

    logfile = fopen(filename, "a");

    fputs(unixtime, logfile);

    fputs(buffer, logfile);

    fputc(94, logfile);
    fputc(10, logfile);

    fclose(logfile);

    free(unixtime);

    return 0;
}