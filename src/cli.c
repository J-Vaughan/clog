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
#include <time.h>
#include <stdlib.h>

#include "cli.h"
#include "eoptions.h"
#include "colours.h"

int options (int argc, char* argv[]) {
    char* argi[argc];
    char* argl[argc];
    int ii = 0;
    char* trash;

    trash = malloc(16);

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            argi[ii] = argv[i];
            argl[ii] = argv[i + 1];
            ii++;
        }
        else if (ii == 0) return 0;
    }

    for (int i = 0; i < ii; i++) {
        if (argi[i][1] == 's') {
            int v = strtol(argl[i], &trash, 10);
            if (v > 0) {
                SHOW_OPTION = 1;
                SHOW_VALUE  = v;
            }
        }
    }

    return 1;
}

int help () {
    #include "help.txt"
    puts(helptxt);

    return 0;
}

/* OLD *************************************************************************
 * int cmdecho (char* buffer) { // TODO: replace this with (pseudo) show(1)
 *     if (printf("\033[34;1m" "%lu: " "\033[0m" "%s\n", (unsigned long) time(NULL), buffer) < 0) {
 *         fprintf(stderr, "Couldn't echo message\n");
 *         return -3;
 *     }
 *
 *     return 0;
 * }
 *
 * int confirm (const char* prompt) {
 *     if (prompt != NULL) {
 *         printf("%s (y/n): ", prompt);
 *         if (fgetc(stdin) == 121) {
 *             return 0;
 *         }
 *         else {
 *             return -1;
 *         }
 *     }
 *     else {
 *         printf("Confirm? (y/n): ");
 *         fgetc(stdin);
 *
 *         if (fgetc(stdin) == 121) {
 *             return 0;
 *         }
 *         else {
 *             return -1;
 *         }
 *     }
 * }
 ******************************************************************************/
