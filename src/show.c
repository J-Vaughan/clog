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

// Version: 0.6.0

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

    for (int i = 0; i < 5; i++) {
        for_buf = fgetc(log_fp);
        if (for_buf != '$') {                                                   // if current character isn't $
            if (i != 0) {                                                         // if current index isn't 0
                buffer[6] = buffer[i - 1];                                          // slot 1 of buffer is index - 1 of length
                buffer[i] = buffer[6];                                              // slot index of length is slot 1 of buffer
                buffer[i - 1] = for_buf;                                            // slot index - 1 of length is current character
                fseek(log_fp, -2, SEEK_CUR);                                        // go back 1 character (for reading)
            }
            else{                                                                 // else if current index is 0
                buffer[i] = for_buf;                                                // slot index of length is
                fseek(log_fp, -2, SEEK_CUR);
            }
        }
        else {
            buffer[i + 1] = '\0';
            break;
        }
    }

    length = strtol(buffer, &buffer+6, 10);

    printf("length = %lu\n", length);

    free(buffer);

    buffer = calloc(MAX_MESSAGE_LEN + DATE_LEN + 4, 1);

    fseek(log_fp, -(length + 2), SEEK_CUR);

    free(buffer);

    return 0;
}
