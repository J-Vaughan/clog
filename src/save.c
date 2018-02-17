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

#include "../lib/sqlite3/sqlite3.h"

#include "save.h"
#include "limits.h"
#include "colours.h"

#include "db.h"

extern int ISDEV;

int parsemessage (int argc, char* argv[], char* buffer) {
    for (int i = 1; i < argc; i++) {
            if (ISDEV == 1) {printf(ANSI_YELLOW "parsemessage>rawargv: " ANSI_RESET "%s\n", argv[i]);}

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
    char* sql_statement = malloc(MAX_MESSAGE_LEN * 2);
    sqlite3_stmt* justwork;
    int result;

    sprintf(sql_statement, 
            "INSERT INTO log VALUES (\'%s\', datetime('now'));", buffer);

    if (ISDEV == 1) printf(ANSI_MAGENTA "%s\n" ANSI_RESET, sql_statement);
    
    result = sqlite3_prepare_v2(db_ptr,
                                sql_statement,
                                strlen(sql_statement),
                                &justwork,
                                NULL);

    if (result != SQLITE_OK) {
        fprintf(stderr, "SQLite Error %i: %s\n", result, sqlite3_errmsg(db_ptr));
            if (ISDEV == 1) puts(ANSI_RED "db>savemessage>prepstmt:badd" ANSI_RESET);
        return -16;
    }

        if (ISDEV == 1) puts(ANSI_GREEN "db>savemessage>prepstmt:succ" ANSI_RESET);

    result = sqlite3_step(justwork);

    if (result != SQLITE_DONE) {
        fprintf(stderr, "SQLite Error %i: %s\n", result, sqlite3_errmsg(db_ptr));
            if (ISDEV == 1) puts(ANSI_RED "db>savemessage>stepstmtt:badd" ANSI_RESET);
        return -17;
    }

        if (ISDEV == 1) puts(ANSI_GREEN "db>savemessage>stepstmt:succ" ANSI_RESET);

    result = sqlite3_finalize(justwork);

    if (result != SQLITE_OK) {
        fprintf(stderr, "SQLite Error %i: %s\n", result, sqlite3_errmsg(db_ptr));
            if (ISDEV == 1) puts(ANSI_RED "db>savemessage>finalstmtt:badd" ANSI_RESET);
        return -18;
    }

        if (ISDEV == 1) puts(ANSI_GREEN "db>savemessage>finalstmt:succ" ANSI_RESET);


    free(sql_statement);

    return 0;
}
