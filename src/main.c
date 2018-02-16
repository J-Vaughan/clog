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
#include <sqlite3.h>

#include "save.h"
#include "main.h"
#include "cli.h"
#include "show.h"
#include "database.h"
#include "limits.h"
#include "boolean.h"
#include "options.h"

int main (int argc, char* argv[])
{
    char* message_buffer;
    sqlite3* log_db;
    int   result;

    if (argc == 1) {
        fprintf(stderr, "Usage: clog [options] message text...\n");
        return -1;
    }

    result = options(argc, argv);
    if (result == TRUE);
    else if (result == FALSE) goto NOOPTIONS;
    else if (result == ERR)
        return -11;

    if (SHOW_OPTION == TRUE) {
        puts("WIP");
	    goto FEND;
    }

    if (HELP == TRUE) {
        help();
        goto END;
    }

    if (VERSION == TRUE) {
        version();
        goto END;
    }

    NOOPTIONS:

    result = open_or_new_db(log_db, 0);

    if (result != 0) {
        fprintf(stderr, "Unable to open database.\n");
        return result;
    }

    message_buffer = malloc(MAX_MESSAGE_LEN);

    result = parsemessage(argc, argv, message_buffer);
    if (result != 0 && result != -10) {
        fprintf(stderr, "Unable to parse message\n");
        return -2;
    }

    result = savemessage(message_buffer);
    if (result != 0) {
        fprintf(stderr, "Unable to save message\n");
        return -4;
    }


    free(message_buffer);

    FEND:
    END:

    return 0;
}
