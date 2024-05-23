/* LICENSE AND CONTACT INFORMATION * * * * * * * * * * * * * * * * * * * * * * *
 * CLog, a logging tool written in C                                           *
 * Copyright (C) 2017-2024 James Vaughan                                            *
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

#include "../lib/sqlite3/sqlite3.h"

#include "show.h"
#include "limits.h"
#include "colours.h"
#include "debug.h"

#include "db.h"

extern int ISDEV;

int show (int amount) {
    sqlite3_stmt* selecter;
    char* dupeded = malloc(64);
    int result;
    int i = 0;

    sprintf(dupeded,
            "SELECT stamp, contents FROM log ORDER BY stamp DESC LIMIT %i;",
            amount);

    result = sqlite3_prepare_v2(db_ptr,
                                dupeded,
                                strlen(dupeded),
                                &selecter,
                                NULL);

    if (result != SQLITE_OK) {
        fprintf(stderr, "SQLite Error %i: %s\n", result, sqlite3_errmsg(db_ptr));
        statreport(2, 3, "show", "database", "prepstmt");
        
        return -19;
    }
    statreport(0, 3, "show", "database", "prepstmt");
    
    result = sqlite3_step(selecter);

    while (result != SQLITE_DONE && result == SQLITE_ROW) {
        printf(ANSI_CYAN "%s> " ANSI_RESET "%s\n",
               sqlite3_column_text(selecter, 0),
               sqlite3_column_text(selecter, 1));
        
        result = sqlite3_step(selecter);
        i++;
    }

    if (i == 0) {
        fprintf(stderr, ANSI_RED "No entries in database, or SQLite error\n" ANSI_RESET);
    }
    else if (i < amount) {
        printf(ANSI_YELLOW "End of entries\n" ANSI_RESET);
    }

    return 0;
}
