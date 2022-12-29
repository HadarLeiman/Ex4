all: Server Client

Server: Server.o DataProcessor.o distance_functions.o KNeighborsClassifier.o input_validation.o
	g++ ./*.o -o Server.out

Client: Client.o DataProcessor.o distance_functions.o KNeighborsClassifier.o input_validation.o
	g++ ./*.o -o Client.out


Client.o: input_validation.h
	g++ -std=c++11 -c Client.cpp

Server.o: input_validation.h
	g++ -std=c++11 -c Server.cpp

input_validation.o: input_validation.cpp input_validation.h DataProcessor.h
	g++ -std=c++11 -c input_validation.cpp

DataProcessor.o: DataProcessor.cpp DataProcessor.h input_validation.h
	g++ -std=c++11 -c DataProcessor.cpp

distance_functions.o: distance_functions.cpp distance_functions.h
	g++ -std=c++11 -c distance_functions.cpp

KNeighborsClassifier.o: KNeighborsClassifier.cpp KNeighborsClassifier.h
	g++ -std=c++11 -c KNeighborsClassifier.cpp

clean:
	rm *.o Client.out
	rm *.o Server.out