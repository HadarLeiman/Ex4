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

    string data ="";
    while(true) {
        bzero(dataFromClient, 4096);
        int read_bytes = recv(this->client_sock, dataFromClient, expected_data_len, 0);
        //TODO what to do in the first and the second case?
        // connection is closed
        if (read_bytes == 0) {
            perror("connection is closed");
            close(client_sock);
            return "error1";
        }// error receiving from client
        else if (read_bytes < 0) {
            perror("error receiving from client");
            close(client_sock);
            return "error2";
        } else if (read_bytes < 4095) {
            cout << "(read_bytes < 4095) "<<read_bytes<<endl;
            data += dataFromClient;
            break;
        } else {
            cout << " data += dataFromClient "<<read_bytes<<endl;
            data += dataFromClient;
        }
    }
    // return the data the client sent
    return data;
}

void SocketIO::write(string str) {
    // send
    char str_to_char_arr[(str).length()];
    strcpy(str_to_char_arr, str.c_str());
    cout<<"socket io about to send"<<endl;
    cout <<str_to_char_arr<<endl;
    if (str.length() > 4095){
        int init_index = 0;
        // send file content in a loop
        while(true) {
            bzero(str_to_char_arr, 4096);
            // substring to send
            string part_of_data_to_send =  str.substr(init_index, 4095);
            strcpy(str_to_char_arr, part_of_data_to_send.c_str());
            int sent_bytes = send(this->client_sock, str_to_char_arr, sizeof(str_to_char_arr), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
                close(client_sock);
            }
            // update substring start position
            init_index += 4095;
            // TODO
            if (part_of_data_to_send.length() < 4095) {
                // done sending file content
                break;
            }
        }
    } else {
        cout << "didn't enter if in socket io write"<<endl;
        int sent_bytes = send(this->client_sock, str_to_char_arr, sizeof(str_to_char_arr), 0);
        if (sent_bytes < 0) {
            perror("error sending to client");
            close(client_sock);
        }
    }
}