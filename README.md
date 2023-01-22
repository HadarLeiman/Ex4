#Ex4 - TCP server-client application.  
This program is a TCP server and client in c++ for Linux.  
Multiple clients can connect to the server using the server's port number.  
Each client connected to the server is handled by a unique thread on the server side and most of the time by two unique threads on the client side (a send thread and a receiver thread that communicate with the server). the exception is on the 5-th command which is explained underneath.  
Each tread on the server side creates a CLI instance which will be in charge of executing the right command for the client user.  

The server provides several actions in a menu display that the client prints to the user of the program to choose from.  
The menu contains the following options:  
1. Upload classified and unclassified CSV files
2. Get or change the algorithm settings (distance metric name/number k), the default values are set to be k=5 and distance metric = EUC.
3. classify the unclassified data file according to the classified data assuming that option 1 was completed before option 3.
4. display the results of the classification assuming option 3 was completed before.
5. download the result to a path in the user's computer specified by him including the name of the file to be created,  again assuming option 3 was completed before. this action happens in a different thread.
8. Exit the program, this option will close the connection of the server and will end the client program. (the server will continue running).

additional information:
The server is running the knn algorithm which was implemented in a previous exercise.  
If the user enters invalid input the program will print "Invalid input" to the screen and continue displaying the menu.  

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


### compile and run the example:  
Compile and run the server:  
<img src="https://user-images.githubusercontent.com/72741540/210270630-672e618a-e945-4c12-807f-c62512b7ca46.png" width="1000" height="300">
Run the Client:  
<img src="https://user-images.githubusercontent.com/72741540/213940985-849bc4f1-a73a-4e75-982a-4d29cf71b489.png" width="1000" height="300">  

<img src="https://user-images.githubusercontent.com/72741540/213941016-71b4c603-ef4c-4292-9303-1c68e92c9abf.png" width="1000" height="300">
