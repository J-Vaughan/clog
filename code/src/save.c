/* LICENSE AND CONTACT INFORMATION * * * * * * * * * * * * * * * * * * * * * * *
 * CLog, a logging tool written in C                                           *
 * Copyright (C) 2018 James Vaughan                                            *
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
#include <unistd.h>

#include "save.h"
#include "limits.h"

int parsemessage (int argc, char* argv[], char* buffer) {
    for (int i = 1; i < argc; i++) {
        if (strlen(buffer) + strlen(argv[i]) <= MAX_MESSAGE_LEN - 1)
            strcat(buffer, argv[i]);
        else {
            fprintf(stderr, "Message too long, saved partial\n");
            return -10;
        }

        if (i != argc - 1) {
            strcat(buffer, " ");
        }
    }

    return 0;
}

int savemessage (char* buffer) {
    FILE*  logfile_fp;
    char*  filename = "log/logfile"; // TODO: user-configurable
    time_t date;
    struct tm *date_tm;
    char   date_s[32];
    int    i = 0;

    date = time(NULL);
    date_tm = localtime(&date);

    strftime(date_s, sizeof(date_s), "%c> ", date_tm); // TODO: error code -5

    if (access("log/", W_OK) != 0) {
        if (mkdir("log", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
            printf("log directory created successfully\n");
        }
        else {
            fprintf(stderr, "Couldn't create log directory\n");
            return -6;
        }
    }

    logfile_fp = fopen(filename, "a");

    if (logfile_fp == NULL) {
        fprintf(stderr, "Couldn't open logfile\n");
        return -7;
    }

    while (buffer[i] != '\0')
        i++;

    fputs(date_s, logfile_fp);
    fputs(buffer, logfile_fp);
    fprintf(logfile_fp, " $%i\n", i);

    // TODO: check if windows and crlf as necessary >> alternatively, not needed since printf does stuff
    // fputc(10, logfile_fp); // \lf

    fclose(logfile_fp);

    return 0;
}