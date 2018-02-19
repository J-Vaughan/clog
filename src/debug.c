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
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "debug.h"
#include "colours.h"

extern int ISDEV;

int statreport (int type, int layers, ...) {
    if (ISDEV == 1); else return 1;

    const int   SLOT_SIZE = 16;
    const char* SEPERATOR = " -> ";

    va_list arglist;
    char* message = malloc(256);
    char* arg_buf = malloc(32);
    int padding;

    // initialize arglist
    va_start(arglist, layers);

    // format args
    for (int i = 0; i < layers; i++) {
        // local copy of arg
        strcpy(arg_buf, va_arg(arglist, char*));

        // padding for visual alignment
        padding = SLOT_SIZE - strlen(arg_buf) - strlen(SEPERATOR);

        if (i == 0) {
            switch (type) {
                case 0:
                    strcpy(message, "success: ");
                    break;
                
                case 1:
                    strcpy(message, "warning: ");
                    break;

                case 2:
                    strcpy(message, "failure: ");
                    break;
            }
        }
    
        strcat(message, arg_buf);

        // seperator
        if (i != layers - 1)
            strcat(message, SEPERATOR);

        // padding
        while (padding > 1) {
            strcat(message, " ");
            padding--;
        }
    }

    // colours
    switch (type) {
        case 0:
            fprintf(stdout, ANSI_GREEN "%s\n" ANSI_RESET, message);
            break;
        
        case 1:
            fprintf(stdout, ANSI_YELLOW "%s\n" ANSI_RESET, message);
            break;

        case 2:
            fprintf(stderr, ANSI_RED "%s\n" ANSI_RESET, message);
            break;
    }

    free(message);
    free(arg_buf);
    va_end(arglist);

    return 0;
}