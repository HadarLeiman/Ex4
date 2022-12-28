//
// Created by USER on 28/12/2022.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "includes/input_validation.h"
using namespace std;

int main(int argc, char** argv){
    // check if number of argument is valid
    if (argc != 3) {
        cout << "Expected 2 arguments but " << argc-1 << " were given" <<  endl;
        return 0;
    }
    // put argument in varibales
    string ip = argv[1];
    string str_port = argv[2];
    //input validation? ip number and port number?
    port_num = port_validation(str_port);
    ip_num = ip_validation(ip)

    const char* ip_address = "127.0.0.1";
    const int port_no = port_num;
    int sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock<0){
        perror("error creating socket");
        }
    struct sockaddr_in sin;
    memset(&sin,0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_num);
    sin.sin_port = htons(port_no);
    if (connect(sock,(struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    while(true){
        //get input from user
        vector<string> userInput;
        getline(cin, userInput);
        //input validation?

//        if (testSampleValidation(inputSample, sampleVector, vecSize)) {
//            sampleVector;
//        }
        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len,0);
        if (sent_bytes < 0){
            // error
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len,0);
        if (read_bytes == 0){
            // connection is closed
        }
        else if (read_bytes < 0) {
            // error
        }
        else {
            cout << buffer;
        }
        close(sock);
        return 0;
    }
}