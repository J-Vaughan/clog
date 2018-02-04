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
#include <stdlib.h>
#include <string.h>

#include "show.h"
#include "limits.h"
#include "colours.h"
#include "utilities.h"

int show (int amount, FILE* log_fp) {
    char* buffer;
    long length;
    char for_buf;
    int  offset;

    // TODO: accomodate cr, crlf, lf
    // TODO: handle fseek errors
    fseek(log_fp, -2, SEEK_END);

    while (amount > 0) {

        buffer = calloc(12, 1);

        // DOCUMENT: !! (too laaaaate)
        for (int i = 0; i < 6; i++) {
            for_buf = fgetc(log_fp);
            fseek(log_fp, -2, SEEK_CUR);

            if (for_buf != '$')
                buffer[i] = for_buf;
            else break;
        }
        
        length = strtol(reversestring(buffer), &buffer + 6, 10);

        free(buffer);

        offset = length + DATE_LEN + 1;

        fseek(log_fp, -(offset), SEEK_CUR);

        for (int i = 0; i < offset; i++) {
            char index = fgetc(log_fp);
            if (i == 0)
                printf(ANSI_CYAN);
            else if (i == DATE_LEN)
                printf(ANSI_RESET);
            putc(index, stdout);
        }

        putc('\n', stdout);

        fseek(log_fp, -(offset + 2), SEEK_CUR);

        amount--;
    }

    return 0;
}
