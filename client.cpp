#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include "input_validation.h"
#include "Command1_UploadData.h"
#include "Command.h"
#include "DefaultIO.h"
#include "StandardIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>

bool downloadFile = false;
string filePath = "";

//this function receive a file path and read the file content into a string.
void readFileToString(string path, string &outputData) {
    ifstream file(path);
    if (file) {
        string line = "";
        while (getline(file, line)) {
            outputData += line;
            outputData += "\n";
        }
        file.close();
    }
    // problem reading file
    if(outputData.size() == 0) {
        cout << "invalid input";
    }
}

// this thread is in charge of receiving messages from the server and printing them to the user.
void *receiveThread(void* s) {
    int *sock = (int*)s;
    while(true) {
        // receive info from server
        char buffer[4096];
        //clean buffer
        bzero(buffer, 4096);
        int expected_data_len = sizeof(buffer);
        
        string data ="";
        // getting the information part by part-if the info is bigger than the buffer size.
        while(true) {
            // receive
            int read_bytes = recv(*sock, buffer, expected_data_len, 0);
            if (read_bytes == 0) {
                // connection is closed
                close(*sock);
                return 0;
            } else if (read_bytes < 0) {
                cout << "Error receiving data from server";
                close(*sock);
                return 0;
            } else if (read_bytes < sizeof(buffer)) {
                //  done receiving the whole message from server.
                data += buffer;
                break;
            } else {
                // saving all parts
                data += buffer;
            }
        }
        string checkForFile = data.substr(0,4);
        if(checkForFile == "file") {
            // delete key word from data
            data = data.substr(4);
            // save the output to a file
            ofstream classifiedFile("classifiedData.csv");
            // Send data to the stream
            classifiedFile << data;
            // Close the file
            classifiedFile.close();
        } else {
            // print the whole message content to the user
            cout << data << flush;
        }
    }
}

// this thread is in charge of sending messages to the server.
void *sendThread(void* s) {
    int* sock = (int*)s;
    while(true) {
        // create a buffer to send user input to the server
        char data_addr[4096];
        // clean the buffer
        bzero(data_addr, 4096);
        // get user input
        string userInput = "";
        getline(cin, userInput);
        if(userInput == ""){
            userInput = "enter";
        }
        strcpy(data_addr, userInput.c_str());
        int data_len = strlen(data_addr);
        // send user choice to server
        int sent_bytes = send(*sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            //error
            cout << "Error sending data to server" << endl;
            close(*sock);
            return 0;
        }
        // if command number 1 - check for file path
        if (userInput == "1") {
            // get user file path for training data
            string train_path = "";
            getline(cin, train_path);
            // save the file content into a string to pass to the buffer
            string train_data = "";
            readFileToString(train_path, train_data);
            // copy the train_data string into the buffer data_addr
            int init_index = 0;
            // send file content part by part in a loop
            while(true) {
                // clean the buffer
                bzero(data_addr, 4096);
                // substring to send in the size of the buffer
                string part_of_file_to_send =  train_data.substr(init_index,4095);
                strcpy(data_addr, part_of_file_to_send.c_str());
                int data_len = strlen(data_addr);
                //send
                int sent_bytes = send(*sock, data_addr, data_len, 0);
                if (sent_bytes < 0) {
                    //error
                    cout << "Error sending data to server" << endl;
                    close(*sock);
                    return 0;
                }
                // update substring start position
                init_index += 4095;
                //TODO better
                if (part_of_file_to_send.length() < 4095) {
                    // done sending file content
                    break;
                }
            }

            //TODO fix handling invalid input
            // get user file path for the validation set
            string test_path = "";
            getline(cin, test_path);
            // save the file into a string to pass to the buffer
            string test_data = "";
            readFileToString(test_path, test_data);
            init_index = 0;
            // send file content part by part in a loop
            while(true) {
                bzero(data_addr, 4096);
                // substring to send in the size of the buffer
                string part_of_file_to_send =  test_data.substr(init_index, 4095);
                strcpy(data_addr, part_of_file_to_send.c_str());
                int data_len = strlen(data_addr);
                //send
                int sent_bytes = send(*sock, data_addr, data_len, 0);
                if (sent_bytes < 0) {
                    //error
                    cout << "Error sending data to server" << endl;
                    close(*sock);
                    return 0;
                }
                // update substring start position
                init_index += 4095;
                if (part_of_file_to_send.length() < 4095) {
                    // done sending file content
                    break;
                }
            }
        } else if (userInput =="5") {
            // update the global variable for the receive-thread to know.
            downloadFile = true;
            string path="";
            getline(cin, path);
            filePath = path;
            // continue the loop to send local path to download the file to
        }
        else if (userInput == "8") {
            // exit
            close(*sock);
            return 0;
        }
    }
}


//this is the main client program
int main(int argc, char** argv) {
    //TODO delete prints
    cout << "this is the client program"<<endl;
    // check if number of argument is valid
    if (argc != 3) {
        cout << "Expected 2 arguments but " << argc - 1 << " were given" << endl;
        return 0;
    }
    // save the arguments inside the corresponding variables
    const char *ip = argv[1];
    string str_port = argv[2];

    // input validation of ip number and port number
    int clientPort;
    if (!portValidation(str_port, clientPort)) {
        cout << "invalid port number" << endl;
        return 0;
    }
    if (!ip_validation(ip)) {
        cout << "invalid ip number" << endl;
        return 0;
    }
    // socket initialization
    const char *ip_address = ip;
    const int port_no = clientPort;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //if socket was successfully created
    if (sock < 0) {
        perror("error creating socket");
        return 0;
    }
    // trying to connect to server
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
        return 0;
    }
    // this loop is in charge of creating threads
    while(true) {
        // the tread identifiers
        pthread_t pthread_receive;
        pthread_t pthread_send;
        // set of thread attributes
        pthread_attr_t attr;
        // set the default attributes of the thread
        pthread_attr_init(&attr);
        //create the threads
        pthread_create(&pthread_receive, &attr, receiveThread, (void *)&sock);
        pthread_create(&pthread_send, &attr, sendThread, (void *)&sock);
        // wait for the threads to exit;
        pthread_join(pthread_receive, NULL);
        pthread_join(pthread_send, NULL);
        close(sock);
        return 0;

    }
}