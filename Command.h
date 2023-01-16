//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_COMMAND_H
#define EX4_COMMAND_H
#include <iostream>
#include <string>
#include "DefaultIO.h"
#include "Data.h"
using namespace std;

class Command {
public:
    string description;
    DefaultIO dio;
    void execute(){};
    Data* data;
};


#endif //EX4_COMMAND_H
