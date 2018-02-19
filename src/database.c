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

#include "../lib/sqlite3/sqlite3.h"

#include "colours.h"
#include "database.h"
#include "debug.h"

#include "db.h"

/* !! fails if log directory does not exist !! */
int open_or_new_db (/* char* custom_name, */ /* sqlite3* db_ptr, */ int scope) {
    // char* db_name;
    // char* db_dir;
    char* db_path = "./log/clog.db";
    int result = 0;

    //if (1 <= scope && scope <= 3); else return -12; // May be used in future

/*  if (custom_name == NULL) { // May be used sometime in the future
        db_name = malloc(16);
        switch (scope) {
            case 1: // local
                db_name = "local_log.db"; // IDEA: possibly use dirname_log
                db_dir  = malloc(5);
                db_dir  = "log/";
            break;
            
            case 2: // git TODO: later
                db_name = "git_repo_log.db"; // IDEA: maybe use reponame_log
                db_dir  = malloc(5);
                db_dir  = "log/";
            break;
            
            case 3: // global TODO: after git
                db_name = "global_log.db"; // IDEA: maybe use username_log
                db_dir  = malloc(5);
                db_dir  = "log/";
            break;
        }

        db_path = malloc(strlen(db_name) + strlen(db_dir));
        strcpy(db_path, db_dir);
        strcat(db_path, db_name);

        free(db_dir);
        free(db_name);
    }
    else {
        db_path = malloc(strlen(custom_name));
        strcpy(db_path, custom_name);
    } 
*/

    result = sqlite3_open_v2(db_path, 
                             &db_ptr, 
                             SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 
                             NULL);

    if (result != SQLITE_OK) {
        fprintf(stderr, "SQLite Error: %s\n", sqlite3_errmsg(db_ptr));
        statreport(2, 3, "database", "openornew", "opendb");

        return -13;
    }
    statreport(0, 3, "database", "openornew", "opendb");

    result = sqlite3_exec(db_ptr,
                          "CREATE TABLE IF NOT EXISTS log (contents varchar(4096), stamp datetime);",
                          NULL,
                          NULL,
                          NULL);
    
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQLite Error: %s\n", sqlite3_errmsg(db_ptr));
        statreport(2, 3, "database", "openornew", "maketable");

        return -15;
    }
    statreport(0, 3, "database", "openornew", "maketable");

    return 0;
}