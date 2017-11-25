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

#include "cli.h"

int cmdecho (char* message_buffer)
{
    if (printf("%lu: %s\n", (unsigned long) time(NULL), message_buffer) < 0)
    {
        fprintf(stderr, "Couldn't echo message\n");
        return -3;
    }

    return 0;
}

int confirm (const char* prompt)
{
    if (prompt != NULL)
    {
        printf("%s (y/n): ", prompt);
        if (fgetc(stdin) == 121)
        {
            putchar(10);
            return 0;
        } else
        {
            putchar(10);
            return -1;
        }
    } else
    {
        printf("(y/n): ");
        if (fgetc(stdin) == 121)
        {
            putchar(10);
            return 0;
        } else
        {
            putchar(10);
            return -1;
        }
    }
}
