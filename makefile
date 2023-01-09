all: main

main: main.c graph.c graph.h
	gcc -Wall -g -o main main.c graph.c
