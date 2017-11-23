CFLAGS = -Wall
CC = gcc
INCLUDES = -Iinc -Isrc
LIBRARIES = 

VPATH = .:./inc:./src
TARGET = clog

$(TARGET): main.o database.o
	$(CC) $(CFLAGS) -o $(TARGET) $(INCLUDES) $(LIBRARIES) main.o database.o

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c $(INCLUDES) $(LIBRARIES)

database.o: database.c
	$(CC) $(CFLAGS) -c database.c $(INCLUDES) $(LIBRARIES)
