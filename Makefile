CFLAGS = -Wall
CC = gcc
INCLUDES = -I./inc
LIBRARIES = 

VPATH = .:./inc:./src
TARGET = clog

$(TARGET): main.o database.o cli.o
	$(CC) $(CFLAGS) -o $(TARGET) $(INCLUDES) $(LIBRARIES) main.o database.o cli.o

main.o:	main.c
	$(CC) $(CFLAGS) -c src/main.c $(INCLUDES) $(LIBRARIES)

database.o: database.c
	$(CC) $(CFLAGS) -c src/database.c $(INCLUDES) $(LIBRARIES)

cli.o: cli.c
	$(CC) $(CFLAGS) -c src/cli.c $(INCLUDES) $(LIBRARIES)

clean:
	$(RM) *.o clog
