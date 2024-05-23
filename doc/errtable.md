<!--
License and Contact Info

CLog, a logging tool written in C
Copyright (C) 2017-2024 James Vaughan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

You can contact me at dev.jamesvaughan@gmail.com with any questions
-->

# CLog Error Table

| Error Code | Description                                                     |
|-----------:|-----------------------------------------------------------------|
|         -1 | Usage error, not enough args given                              |
|         -2 | `parsemessage` returned an error                                |
|         -3 | `cmdecho` returned an error                                     |
|         -4 | `savemessage` returned an error                                 |
|         -5 | Couldn't format Unix time                                       |
|         -6 | Couldn't create directory                                       |
|         -7 | Couldn't open file                                              |
|         -8 | `fstat` returned an error                                       |
|         -9 | Couldn't find line size                                         |
|        -10 | Message was too long, but con'd successfully                    |
|        -11 | Finding options failed                                          |
|        -12 | Invalid db scope                                                |
|        -13 | sqlite3 db opening/creating error                               |
|        -14 | sqlite3 db closing error                                        |
|        -15 | sqlite3 db making table if not exists error                     |
|        -16 | sqlite3 db saving message statement prep error                  |
|        -17 | sqlite3 db saving message statement step error                  |
|        -18 | sqlite3 db saving message statement finalize error              |
|        -19 | sqlite3 db showing message statement prep error                 |
|        -20 | message includes ' character, which is bad                      |
<!----------------------------------------------------------------------------->

Add rows as necessary.
