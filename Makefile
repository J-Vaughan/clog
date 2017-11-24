CFLAGS = -Wall -std=gnu99
CC = gcc
INCLUDES = -I./inc
LIBRARIES = 

VPATH = .:./inc:./src
TARGET = clog

$(TARGET): bindir |  main.o database.o cli.o
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(INCLUDES) $(LIBRARIES) main.o database.o cli.o

bindir:
	if [ ! -d "bin" ]; \
		then mkdir "bin"; \
	fi

main.o:	main.c
	$(CC) $(CFLAGS) -c src/main.c $(INCLUDES) $(LIBRARIES)

database.o: database.c
	$(CC) $(CFLAGS) -c src/database.c $(INCLUDES) $(LIBRARIES)

cli.o: cli.c
	$(CC) $(CFLAGS) -c src/cli.c $(INCLUDES) $(LIBRARIES)

.PHONY: clean
clean:
	$(RM) *.o clog
