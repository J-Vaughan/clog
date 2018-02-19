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
#include "colours.h"
#include "debug.h"

sqlite3* db_ptr;

const int ISDEV = 0; // toggles semi-valuable output (1 = on)

int main (int argc, char* argv[])
{
    char*   message_buffer; // holds parsed message
    int     result;         // holds result of methods (for error testing)

    // no arguments given (at all)
    if (argc == 1) {
        fprintf(stderr, "Usage: clog [options] message text...\n");
        statreport(2, 2, "main", "arguments");

        return -1;
    }
    statreport(0, 2, "main", "arguments");

    // tests whether any options were given
    result = options(argc, argv);

    // if options were given, continue to option tree
    if (result == TRUE);

    // if no options were given, skip option tree
    else if (result == FALSE) goto NOOPTIONS;

    // if options somehow returns an error, panic
    else if (result == ERR) {
        fprintf(stderr, ANSI_RED "Error detecting options\n" ANSI_RESET);
        statreport(2, 4, "main", "arguments", "options", "detection");

        return -11;
    }

    // if -s [x] or --show [x] was passed
    if (SHOW_OPTION == TRUE) {
        // open the db and create table 
        result = open_or_new_db(0);

        // yep
        if (result != 0) 
            puts(ANSI_RED "!!HAVEN'T HANDLED THIS YET!!" ANSI_RESET);

        show(SHOW_VALUE);
	    goto FEND;
    }

    if (HELP == TRUE) {
        help();
        statreport(0, 2, "main", "help");

        goto END;
    }

    if (VERSION == TRUE) {
        version();
        statreport(0, 2, "main", "version");

        goto END;
    }

    NOOPTIONS:

    result = open_or_new_db(0);

    if (result != 0) {
        fprintf(stderr, ANSI_RED "Unable to open database.\n" ANSI_RESET);
        statreport(2, 3, "main", "database", "opening");
        
        return result;
    }
    statreport(0, 3, "main", "database", "opening");

    message_buffer = calloc(MAX_MESSAGE_LEN, 1);

    result = parsemessage(argc, argv, message_buffer);

    if (result != 0 && result != -10) {
        fprintf(stderr, "Unable to parse message\n");
        statreport(2, 2, "main", "parsemessage");

        return -2;
    }
    statreport(0, 2, "main", "parsemessage");

    result = savemessage(message_buffer);

    if (result != 0) {
        fprintf(stderr, "Unable to save message\n");
        statreport(2, 2, "main", "savemessage");

        return -4;
    }
    statreport(0, 2, "main", "savemessage");

    free(message_buffer);
    statreport(1, 2, "main", "freedbuf");

    show(1);
    statreport(0, 3, "main", "show", "(parsed)");

    FEND:

    result = sqlite3_close_v2(db_ptr);

    if (result != SQLITE_OK) {
        fprintf(stderr, ANSI_RED "Error when closing db: %s\n", sqlite3_errmsg(db_ptr));
        statreport(2, 3, "main", "database", "closing");

        return -14;
    }
    statreport(0, 3, "main", "database", "closing");

    END:

    return 0;
}
