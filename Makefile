#!/bin/bash

CC=g++
CFLAGS= -ansi -O5 -Wall
LDFLAGS= -ansi -lm -Wall
EXEC=community convert hierarchy
OBJ1= graph_binary.o community.o
OBJ2= graph.o

all: $(EXEC)

community : $(OBJ1) main_community.o
	$(CC) -o $@ $^ $(LDFLAGS)

convert : $(OBJ2) main_convert.o
	$(CC) -o $@ $^ $(LDFLAGS)

hierarchy : main_hierarchy.o
	$(CC) -o $@ $^ $(LDFLAGS)

bin:
	$(CC) main.cc -g graph_gen.cpp -pthread -o tbin
	make cl
##########################################
# Generic rules
##########################################

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
cl:
	${RM} cavemans/*  bins/* trees/* Result.txt
clean:
	rm -f *.o *~ $(EXEC) 
