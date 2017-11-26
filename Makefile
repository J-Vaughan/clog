CFLAGS = -Wall -std=gnu99
CC = gcc
INCLUDES = -I./inc
LIBRARIES =

VPATH = .:./inc:./src
TARGET = clog

$(TARGET): bindir |  main.o database.o cli.o save.o
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(INCLUDES) $(LIBRARIES) main.o database.o cli.o save.o

bindir:
	@if [ ! -d "bin" ]; \
		then mkdir "bin"; \
	fi

main.o:	main.c
	$(CC) $(CFLAGS) -c src/main.c $(INCLUDES) $(LIBRARIES)

database.o: database.c
	$(CC) $(CFLAGS) -c src/database.c $(INCLUDES) $(LIBRARIES)

cli.o: cli.c
	$(CC) $(CFLAGS) -c src/cli.c $(INCLUDES) $(LIBRARIES)

save.o: save.c
	$(CC) $(CFLAGS) -c src/save.c $(INCLUDES) $(LIBRARIES)

.PHONY: clean
clean:
	$(RM) *.o clog

.PHONY: install
install:
	mv bin/clog /usr/bin/

.PHONY: uninstall
uninstall:
	rm -f /usr/bin/clog
