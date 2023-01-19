//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_COMMAND_H
#define EX4_COMMAND_H
#include <iostream>
#include <string>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "Data.h"
using namespace std;

class Command {
public:
    virtual ~Command(){}
    string description;
    DefaultIO* dio;
    virtual void execute()=0;
    Data* data;
};


#endif //EX4_COMMAND_H
