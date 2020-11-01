CC=g++
CFLAGS=-std=c++17 -pedantic
OUTPUT=oop_exercise_04

all:
	$(CC) $(CFLAGS) main.cpp -o $(OUTPUT)
run:
	./$(OUTPUT)