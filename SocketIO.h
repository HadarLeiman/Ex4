//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_SOCKETIO_H
#define EX4_SOCKETIO_H
#include "DefaultIO.h"
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

class SocketIO : public DefaultIO{
    int client_sock;
public:
    SocketIO(int client_sock);
    string read();
    void write(string str);
};


#endif //EX4_SOCKETIO_H
