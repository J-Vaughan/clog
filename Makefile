CFLAGS = -Wall
CC = gcc
INCLUDES = -I./inc
LIBRARIES = 

VPATH = .:./inc:./src
TARGET = clog

$(TARGET): main.o database.o
	$(CC) $(CFLAGS) -o $(TARGET) $(INCLUDES) $(LIBRARIES) main.o database.o

main.o:	main.c
	$(CC) $(CFLAGS) -c src/main.c $(INCLUDES) $(LIBRARIES)

database.o: database.c
	$(CC) $(CFLAGS) -c src/database.c $(INCLUDES) $(LIBRARIES)

clean:
	$(RM) *.o clog
