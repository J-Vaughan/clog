# License and Contact Info
# 
# CLog, a logging tool written in C
# Copyright (C) 2017 James Vaughan
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 
# You can contact me at dev.jamesvaughan@gmail.com with any questions

CFLAGS = -Wall -std=gnu99 -Os
CC = gcc
INCLUDES = -I./inc
LIBRARIES =
INTERNAL_LIBRARIES = lib/sqlite3/sqlite3.c -lpthread -ldl

VPATH = .:./inc:./src
TARGET = clog

$(TARGET): bindir |  main.o database.o cli.o save.o show.o debug.o Makefile
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(INCLUDES) $(LIBRARIES) $(INTERNAL_LIBRARIES) \
	 main.o database.o cli.o save.o show.o debug.o

bindir:
	@if [ ! -d "bin" ]; \
		then mkdir "bin"; \
	fi

main.o:	main.c
	$(CC) $(CFLAGS) -c src/main.c $(INCLUDES) $(LIBRARIES)

database.o: database.c
	$(CC) $(CFLAGS) -c src/database.c $(INCLUDES) $(LIBRARIES)

cli.o: cli.c help.txt version.h
	$(CC) $(CFLAGS) -c src/cli.c $(INCLUDES) $(LIBRARIES)

save.o: save.c
	$(CC) $(CFLAGS) -c src/save.c $(INCLUDES) $(LIBRARIES)

show.o: show.c
	$(CC) $(CFLAGS) -c src/show.c $(INCLUDES) $(LIBRARIES)

debug.o: debug.c
	$(CC) $(CFLAGS) -c src/debug.c $(INCLUDES) $(LIBRARIES)

.PHONY: clean
clean:
	$(RM) *.o clog

.PHONY: install
install:
	mv bin/clog /usr/bin/

.PHONY: uninstall
uninstall:
	rm -f /usr/bin/clog

.PHONY: dev
dev:
	make
	mv bin/$(TARGET) ~/bin/
	make clean
