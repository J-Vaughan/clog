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

// Version: 0.6.2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "show.h"
#include "limits.h"

int show (int amount, FILE* log_fp) {
    char* buffer;
    long length;
    char for_buf;

    buffer = malloc(6);

    // TODO: handle fseek errors

    fseek(log_fp, -2, SEEK_END);

    // DOCUMENT: !!
    for (int i = 0; i < 5; i++) {
        for_buf = fgetc(log_fp);
        if (for_buf != '$') {
            if (i != 0) {
                buffer[6] = buffer[i - 1];
                buffer[i] = buffer[6];
                buffer[i - 1] = for_buf;
                fseek(log_fp, -2, SEEK_CUR);
            }
            else{
                buffer[i] = for_buf;
                fseek(log_fp, -2, SEEK_CUR);
            }
        }
        else {
            buffer[i + 1] = '\0';
            break;
        }
    }

    length = strtol(buffer, &buffer+6, 10);

    free(buffer);

    buffer = calloc(MAX_MESSAGE_LEN + DATE_LEN + 4, 1);

    fseek(log_fp, -(length + DATE_LEN + 3), SEEK_CUR);

    // TODO: errcheck
    fgets(buffer, length + DATE_LEN + 2, log_fp);

    puts(buffer);

    free(buffer);

    return 0;
}
