# Ex3
This program is a TCP server and client in c++ for Linux.  
Clients are able to connect to the server using the server's port number and ask it for samples classification of specific data vectors.  
The server is running the knn algorithm and returns a predicted classification for the client which the client prints to the user.  
This directory contains 2 executable programs that can be created using the 'make' command.  
The server program is initialized with 2 command line arguments:  
(1) path to a dataset file.  
(2) port number.  
The client program is also initialized with 2 command line arguments:  
(1) IP number of the user using the program.  
(2) port number of the server to connect to.  
In general time the server is waiting for the clients, the server can take care of one client at a time. when a client is done using the server it sends (-1) to the server and closes the socket. the server is now open for other clients.
If a new client is trying to connect to the server while the server is connected to a former client the communication with the new client will stay on wait.
If the user enters an invalid input the program will print "Invalid input" message to the screen and ask the user to re-enter his input.


## **How to Install and Run (UNIX users):**
1. Download files
2. Open the terminal
3. Install a c++ compiler (If you don't have one installed)
4. run `make`
5. run `./server.out [Path_to_csv_file] [Port number]`
   run `./client.out [IP number] [Port number]`


## **How to use:**
In the client program Insert the vector sample as a string of numbers with spaces between them a distance metric name and a number k.  
`[vector] [metric] [k]`
  
where k is an integer and a valid distance function name is one of the following:  
AUC (for Euclidean distance), MAN (for Manhattan distance), CHB (for Chebyshev distance), CAN (for Canberra distance) or MIN (for Minkowski distance)
for example: `1 2 3`. Then press enter. 
the input vector needs to be in the same size as the vectors in the training data.  
The label prediction will be printed on the screen.  
In case of invalid sample input, An error message will be printed.  
The program will continue to receive sample vectors in an infinite loop.

### compile and run the example:  
<img src="https://user-images.githubusercontent.com/72741540/207402120-c71721bc-94f0-4884-ab2e-482e2ebb4ea2.png" width="350" height="180">

