#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cmath>
#include <unistd.h>
using namespace std;
#include <string>
#include <string.h>
#include <cstring>
#include<algorithm>
#include <vector>
#include "includes/input_validation.h"

//TODO *****************
//TODO get rid of prints: port number, ip number, vector, data_addr print, split user input
//TODO *****************

int main(int argc, char** argv){
    // check if number of argument is valid
    if (argc != 3) {
        cout << "Expected 2 arguments but " << argc-1 << " were given" <<  endl;
        return 0;
    }
    //save the arguments inside the corresponding variables
    const char* ip = argv[1];
    string str_port = argv[2];

    //TODO input validation of ip number and port number
    int clientPort;
    if (!portValidation(str_port, clientPort)) {
        cout<<"invalid port number";
        return 0;
    }
    if (!ip_validation(ip)){
        cout<<"invalid ip number";
        return 0;
    }
    //socket initialization
    const char* ip_address = ip;
    const int port_no = clientPort;
    int sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock<0){
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin,0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock,(struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    while(true){
        //get user input.
        string userInput;
        getline(cin, userInput);
        if (userInput=="-1"){
            //close the program
            close(sock);
            return 0;
        }
        //split the user input into 3 relevant inputs - vector, function name and number k.
        string str_vec;
        string distance_metric_name;
        string str_k;
        splitUserInput(userInput,str_vec, distance_metric_name, str_k);

        //sample vector validation before sending it to the server for classification
        vector<double> sample_vec;
        int k;
        //getting vector size
        int sample_vec_size = (str_vec).length()-(str_vec).length()/2;
        //send a fake size
        //TODO (sample vector size == train vectors size) in server?
        //send infinity as vector size or the same vector size?
        if (!testSampleValidation(str_vec, sample_vec, sample_vec_size)){
            cout<<"user vector is invalid"<<endl;
            //cout << "invalid input";
        }
        else if (!DistFuncValid(distance_metric_name)){
            cout<<"user metric function is invalid"<<endl;
            //cout << "invalid input";
        }
        //TODO (k < train samples size) check in server?
        else if(!isInteger(str_k)){
            cout<<"user k number is invalid"<<endl;
            //cout << "invalid input";
        }
        //save the user vector as data to send
        char data_addr[(str_vec).length()];
        strcpy(data_addr, str_vec.c_str());
        //TODO delete
        cout<<data_addr;
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
            //print the classification
            cout << buffer;
        }
        close(sock);
        return 0;
    }
}