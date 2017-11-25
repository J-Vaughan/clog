/* HEADER PROLOG * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * NAME:                                                                       *
 *                                                                             *
 * PURPOSE:                                                                    *
 *                                                                             *
 * GLOBAL VARIABLES:                                                           *
 *                                                                             *
 * Variable             Type      Description                                  *
 * --------             ----      -----------                                  *
 *                                                                             *
 * DEVELOPMENT HISTORY: (STILL REQUIRED IF USING A VCS)                        *
 *                                                                             *
 * Date       Author    Minor     Release   Description                        *
 * ----       ------    -----     -------   -----------                        *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef cli_h
#define cli_h

int cmdecho (int argc, char* argcv[], char* message_buffer);

int confirm (const char* prompt);

#endif
