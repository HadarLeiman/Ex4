#Ex4 - TCP server multi-client and multi-threads
This program is a TCP server and client in c++ for Linux.
Multiple clients can connect to the server at the same time using the server's port number and choose an action from the given menu.
the server has 5 options on the menu:
1. upload an unclassified csv data file
2. algorithm settings
3. classify data
4. display results
5. download results
8. exit

In general speaking, the server can classify an unclassified file that the user uploaded after he uploaded a classified file.
the user can ask to see or change the settings of the knn algorithm acting on the server side, the program would display the current distance metric name and the number k of the algorithm.
the user can choose to download the results of the classification to a specified path on his computer.
The server is running the knn algorithm (which we implemented in a previous exercise) and returns a predicted classification of the client's unclassified file to the client/user.
the server is waiting for the clients, the server can take care of multiple clients in parallel by creating a new thread for each client accepted by the socket. when a user is done using the server services it can choose (8) from the menu to exit the program, in that case the client closes the connection to the server. The server stayes open for his clients and will continue accepting new clients. while the is client connected it will continue o send and receive messages from the server, if the user input is invalid the program will print "Invalid input" to the screen and continue displaying the menu.
Inside the client program after secssesfully connecting to the server socket the program creates two threads a send thread and a receive thread.
in the case the users chooses 5 from the menu the client program creates another thread that will save the file content in the user computer.

This directory contains 2 executable programs that can be created using the 'make' command.

The server program is initialized with 1 command line arguments:
(1) port number.
The client program can be initialized with 2 command line arguments:
(1) IP number of the user using the program.
(2) port number of the server to connect to.


## **How to Install and Run (UNIX users):**
1. Download files
2. Open the terminal
3. Install a c++ compiler (If you don't have one installed)
4. run `make`  

for server run ./server.out [Port number]
for client run ./client.out [IP number] [Port number]
How to use:


compile and run the example:
Compile and run the server:
