/* LICENSE AND CONTACT INFORMATION * * * * * * * * * * * * * * * * * * * * * * *
 * CLog, a logging tool written in C                                           *
 * Copyright (C) 2017 James Vaughan <dev.jamesvaughan@gmail.com>               *
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
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* FILE PROLOG * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * FILE NAME: database.c                                                       *
 *                                                                             *
 * PURPOSE: Manage the database connections                                    *
 *                                                                             *
 * FILE REFERENCES:                                                            *
 *                                                                             *
 * Name                      Description                                       *
 * ----                      -----------                                       *
 * globals.h                 Contains global file*s, etc.                      *
 *                                                                             *
 * EXTERNAL VARIABLES:                                                         *
 * Source: < globals.h >                                                       *
 *                                                                             *
 * Name       Type           Description                                       *
 * ----       ----           -----------                                       *
 * db         sqlite3        Global database pointer                           *
 *                                                                             *
 * EXTERNAL REFERENCES: none                                                   *
 *                                                                             *
 * Name                     Descripton                                         *
 * ----                     ----------                                         *
 *                                                                             *
 * ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES:                *
 *                                                                             *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:                                     *
 *                                                                             *
 * NOTES:                                                                      *
 *                                                                             *
 * REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:                          *
 *                                                                             *
 * DEVELOPMENT HISTORY: (STILL REQUIRED IF USING A VCS)                        *
 *                                                                             *
 * Date       Author    Minor     Release   Description                        *
 * ----       ------    -----     -------   -----------                        *
 *                                                                             *
 * ALGORITHM (PDL)                                                             *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
