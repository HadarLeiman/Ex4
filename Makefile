all: Server Client

Server: Server.o DataProcessor.o distance_functions.o KNeighborsClassifier.o input_validation.o
	g++ -std=c++11 -c Server.cpp

Client: Client.o input_validation.o
	g++ -std=c++11 -c Client.cpp

clean:
	@rm -f *.o