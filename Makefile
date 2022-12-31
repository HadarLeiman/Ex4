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


all: $(BUILD_FILES) Server.o Client.o
	$(CC) $(BUILD_FILES) Server.o -o Server.out
	$(CC) $(BUILD_FILES) Client.o -o Client.out

run: $(BUILD_FILES) Server.o Client.o
	$(CC) $(BUILD_FILES) Server.o -o Server.out & $(CC) $(BUILD_FILES) Client.o -o Client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

Server.o: Server.cpp
	$(CC) -c -o Server.o Server.cpp
Client.o: Client.cpp
	$(CC) -c -o Client.o Client.cpp

# Clean command
clean:
	$(CLN) *.o Server.out Client.out