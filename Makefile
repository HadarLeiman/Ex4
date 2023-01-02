# Makefile for running two programs

# Choose the compiler.
CC = g++ -std=c++11
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

BUILD_FILES += distance_functions.o
BUILD_FILES += DataProcessor.o
BUILD_FILES += input_validation.o
BUILD_FILES += KNeighborsClassifier.o


all: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out
	$(CC) $(BUILD_FILES) client.o -o client.out

run: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out & $(CC) $(BUILD_FILES) client.o -o client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

server.o: server.cpp
	$(CC) -c -o server.o server.cpp
client.o: client.cpp
	$(CC) -c -o client.o client.cpp

# Clean command
clean:
	$(CLN) *.o server.out client.out