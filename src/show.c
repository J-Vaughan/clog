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

// Version: 0.5.10

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "show.h"
#include "limits.h"

int show (int amount, FILE* log_fp) {
    char* buffer;
    unsigned long unixtime;
    int log_fn;
    struct stat log_st;
    long long log_size;
    int iterator = 1;
    int looper = 0;

    log_fn = fileno(log_fp);

    if (fstat(log_fn, &log_st) != 0) {
        fprintf(stderr, "Couldn't get log files stats\n");
        return -8;
    }

    log_size = (long long) log_st.st_size;

    buffer = malloc(MAX_MESSAGE_LEN);

    // TODO: handle fseek errors

    RETRY:

    fseek(log_fp, -iterator, SEEK_END);

    if (fgetc(log_fp) != '^') {
        looper++;
        iterator++;
        if (iterator >= 5) {
            fprintf(stderr, "Couldn't find ending caret\n");
            return -9;
        }
        goto RETRY;
    }

    iterator += 1;

    fseek(log_fp, -iterator, SEEK_END);

    CAPTURE:

    if (iterator >= MAX_MESSAGE_LEN - 2) goto END;

    buffer[iterator - 3] = fgetc(log_fp);
    printf("%c at %i\n", buffer[iterator - 3], iterator);

    free(buffer);

    END:

    return 0;
}
