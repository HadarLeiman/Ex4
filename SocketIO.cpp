//
// Created by Hadar on 15/01/2023.
//

#include "SocketIO.h"

SocketIO::SocketIO(int client_sock){
    this->client_sock = client_sock;
}

string SocketIO::read(){
    // receive
    char dataFromClient[4096];
    bzero(dataFromClient, 4096);
    int expected_data_len = sizeof(dataFromClient);
    int read_bytes = recv(this->client_sock, dataFromClient, expected_data_len, 0);
    //TODO what to do in the first and the second case?

    // connection is closed
    if (read_bytes == 0) {
        perror("connection is closed");
        close(client_sock);
    }
    // error receiving from client
    else if (read_bytes < 0) {
        perror("error receiving from client");
        close(client_sock);
    }
    // return the data the client sent
    else{
        return dataFromClient;
    }
}

void SocketIO::write(string str) {
    // send
    char str_to_char_arr[(str).length()];
    strcpy(str_to_char_arr, str.c_str());
    int sent_bytes = send(this->client_sock, str_to_char_arr, sizeof(str_to_char_arr), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
        close(client_sock);
    }
}