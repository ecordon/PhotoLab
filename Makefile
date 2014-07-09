# Makefile for PhotoLab program

CC = gcc
CFLAGS = -c -Wall
OBJECTS = PhotoLab.o DIPs.o Advanced.o FileIO.o Image.o
EXECUTABLE = PhotoLab

all: $(OBJECTS) $(EXECUTABLE)
clean: 
	rm $(OBJECTS) $(EXECUTABLE)

PhotoLab: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c

FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c

DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c

Advanced.o: Advanced.c Advanced.h Image.h
	$(CC) $(CFLAGS) Advanced.c

PhotoLab.o: PhotoLab.c Advanced.h DIPs.h FileIO.h Image.h
	$(CC) $(CFLAGS) PhotoLab.c

