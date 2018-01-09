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

// Version: 0.5.9

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "save.h"
#include "main.h"
#include "cli.h"
#include "show.h"
#include "limits.h"

int main (int argc, char* argv[])
{
    char* message_buffer = malloc(MAX_MESSAGE_LEN);
    FILE* test_fp;

    if (argc == 1) {
        fprintf(stderr, "Usage: clog <message>\n");
        return -1;
    }

    if (parsemessage(argc, argv, message_buffer) != 0) {
        fprintf(stderr, "Unable to parse message\n");
        return -2;
    }

    if (savemessage(message_buffer) != 0) {
        fprintf(stderr, "Unable to save message\n");
        return -4;
    }

    cmdecho(message_buffer);

    free(message_buffer);

    test_fp = fopen("log/logfile", "r");

    show(1, test_fp);

    fclose(test_fp);

    return 0;
}
