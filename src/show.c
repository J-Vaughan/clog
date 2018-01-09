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

// Version: 0.5.9

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

    log_fn = fileno(log_fp);

    if (fstat(log_fn, &log_st) != 0) {
        fprintf(stderr, "Couldn't get log files stats\n");
        return -8;
    }

    log_size = (long long) log_st.st_size;

    buffer = malloc(MAX_MESSAGE_LEN);

    // TODO: handle fseek errors



    for (int i = 0; i < amount; i++) {

        if (fscanf(log_fp, "%lu %*2c", &unixtime) < 0) {
            fprintf(stderr, "Couldn't scan time from log\n");
            return -8;
        }

        for (int ii = 0; i < MAX_MESSAGE_LEN - 1; ii++) {
            buffer[ii] = fgetc(log_fp);

            if (buffer[ii] == 94) {
                buffer[ii] = 0;
                break;
            }
        }

        if (printf("\033[34;1m" "%lu: " "\033[0m" "%s\n", unixtime, buffer) < 0) {
            fprintf(stderr, "Couldn't print message\n");
            return -9;
        }
    }

    free(buffer);

    return 0;
}
