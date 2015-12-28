
CC=gcc
CFLAGS=-g -Wall -c -DDEBUG
LDFLAGS=-lm #-lpthread

SOURCES=spanningTree.c readFile.c log.c
OBJECTS=$(SOURCES:.c=.o)


EXECUTABLE=spanningTree

all: $(SOURCES) spanningTree

${EXECUTABLE}: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@


.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf ${EXECUTABLE} *.o core
